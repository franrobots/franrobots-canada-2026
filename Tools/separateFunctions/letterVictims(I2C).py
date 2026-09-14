# Letter victim scanner
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
                print("-------")
                ledB.on()
                time.sleep_ms(30)
            else:
                print(f"[I2C] Comando inválido: {cmd}")
    except Exception as e:
        pass

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

    result = detect_letter(img)

    # 3. buffer updates anyways
    buffer[0] = result[0]
    buffer[1] = result[1]

    # print("Resultado:", result)

    send_I2C()
    ledB.off()
    print(".")
    # print("FPS:", clock.fps())
