# V1.3.2-Beta: pooling fps, optmizing code
import sensor, ml, uos, gc, time, pyb
from machine import LED
clock = time.clock()

# -------------- inicialization --------------
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_hmirror(True)
sensor.set_vflip(True)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)

ledB = LED("LED_BLUE")

# -------------- Machine Learning --------------
try:
    # load the model, alloc the model file on the heap if we have at least 64K free after loading
    net = ml.Model("main.tflite", load_to_fb=uos.stat('main.tflite')[6] > (gc.mem_free() - (64*1024)))
except Exception as e:
    print(e)
    raise Exception('Failed to load "main.tflite", did you copy the .tflite and labels.txt file onto the mass-storage device? (' + str(e) + ')')

labels = [line.rstrip("\n") for line in open("labels.txt")]

# -------------- Calibration --------------
# Thresholds LAB
thresholds = {
    "black": (2, 10, -11, 10, 1, 10),
    "red": (8, 16, -6, 28, 9, 21),
    "yellow": (74, 93, -18, 7, 25, 58),
    "green": (10, 22, -27, -12, -5, 22),
    "blue": (8, 25, -14, 6, -28, -5)
}

# --------- Victims Variables ---------
# Color values
color_values = {
    "black": -2,
    "red": -1,
    "yellow": 0,
    "green": 1,
    "blue": 2,
}

# Letter values
letter_values = {
    "omega": 0,
    "psi": 1,
    "phi": 2,
}

# Confidence to accept the victim
MIN_CONFIDENCE = 87

# votes used to set the ring color
votes = {
    "unknown": 0,
}

for color in thresholds:
    votes[color] = 0

# Circle radius separation (in percentage)
distances = [0.1, 0.3, 0.5, 0.7, 0.9]

# Cardinalities
directions = [
    (1, 0),   # Right
    (-1, 0),  # Left
    (0, 1),   # Top
    (0, -1),  # Bottom
]

# -------------- I2C Protocol --------------
# Cam Left
I2C_ADDR = 0x12

bus = pyb.I2C(2, pyb.I2C.SLAVE, addr=I2C_ADDR)

buffer = bytearray([0, 0])  # [valor identificado, confiabilidade]


def send_I2C():
    try:
        cmd = bus.recv(1, timeout=1000)
        if cmd:
            print("[I2C] Command Recieved:", hex(cmd[0]))
            if cmd[0] == 0x00:
                bus.send(buffer)
                print("[I2C] Enviado:", buffer[0], buffer[1])
                time.sleep_ms(30)
                ledB.on()
            else:
                print(f"[I2C] Comando inválido: {cmd}")
    except Exception as e:
        pass

# -------------- Color process --------------


def read_color(x, y):
    stats = img.get_statistics(roi=(x, y, 3, 3))  # Get LAB info 3x3 pixel
    L = stats.l_mean
    A = stats.a_mean
    B = stats.b_mean

    for color_name, th in thresholds.items():
        if (th[0] <= L <= th[1] and
                th[2] <= A <= th[3] and
                th[4] <= B <= th[5]):
            return color_name
    return "unknown"


def validate_victims(colors):
    total_points = 0

    for color in (colors):
        if color == "unknown":
            return [0, 0]

        total_points += color_values[color]

    if 0 <= total_points <= 2:
        return [total_points, 100]

    return [0, 0]


def detect_circle_victim(img):
    colors = []
    # Image processing (to identify yellow circles)
    img_binary = img.copy()
    img_binary.binary([thresholds["yellow"]])
    img_binary.erode(1)
    img_binary.dilate(1)

    circles = img_binary.find_circles(threshold=5000, r_min=50, r_max=95, x_margin=35, y_margin=35, r_margin=12)
    if not circles:
        circles = img.find_circles(threshold=5000, r_min=50, r_max=95, x_margin=35, y_margin=35, r_margin=12)
    if circles:
        c = max(circles, key=lambda c: c.r)

        cx = c.x
        cy = c.y
        cr = c.r

        # For each ring
        for radius_ratio in distances:
            offset = int(cr * radius_ratio)  # Offset from the center of the circle to each ring

            for color in thresholds:
                votes[color] = 0

            votes["unknown"] = 0

            # Goes around the ring
            for dx, dy in directions:
                x = cx + (offset * dx)
                y = cy + (offset * dy)

                sample_color = read_color(x, y)  # Get color
                img.draw_circle((x, y, 3), color=(255, 0, 0))  # Drawing

                votes[sample_color] += 1

            colors.append(max(votes, key=votes.get))
        print(colors)

        # Debug draw
        img.draw_circle((cx, cy, cr), color=(255, 0, 0))
        img.draw_cross((cx, cy), color=(255, 255, 0))

        # print(colors)
        return validate_victims(colors)
    return [0, 0]

# -------------- Letter process --------------


def detect_letter(img):
    prediction = net.predict([img])[0].flatten().tolist()
    max_index = prediction.index(max(prediction))

    label = labels[max_index]
    confidence = prediction[max_index]

    if label == "unknown" or confidence <= MIN_CONFIDENCE / 100:
        return [0, 0]

    return [letter_values[label], int(confidence * 100)]


# =======================================
# ============== Main Loop ==============

while True:
    clock.tick()
    img = sensor.snapshot()

    # 1. Search for color victims
    result = detect_circle_victim(img)

    # 2. if not exists a valid vitcim color, search for ML
    if not (0 <= result[0] <= 2 and result[1] > MIN_CONFIDENCE):
        result = detect_letter(img)

    # 3. buffer updates anyways
    buffer[0] = result[0]
    buffer[1] = result[1]

    print("Resultado:", result)

    send_I2C()
    print("FPS:", clock.fps())
