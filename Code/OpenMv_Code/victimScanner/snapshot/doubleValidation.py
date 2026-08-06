# V1.2.1-Snapshot: Getting both circles with 2 find_circle() + yellow binary
import sensor

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(True)
sensor.set_vflip(True)
sensor.skip_frames(time=2000)

colors = []
circles = []

# Thresholds LAB
thresholds = {
    "black": (5, 29, -14, 3, -24, 12),
    "red": (30, 43, 24, 43, 7, 24),
    "yellow": (51, 74, -26, 4, 16, 34),
    "green": (41, 62, -28, -5, -22, 17),
    "blue": (41, 58, -16, 2, -39, -15)
}

# Color values
color_values = {
    "black": -2,
    "red": -1,
    "yellow": 0,
    "green": 1,
    "blue": 2,
}

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


def read_color(x, y):
    stats = img.get_statistics(roi=(x, y, 3, 3))  # Get LAB info 3x3 pixel
    L = stats.l_mean()
    A = stats.a_mean()
    B = stats.b_mean()

    for color_name, th in thresholds.items():
        if (th[0] <= L <= th[1] and
                th[2] <= A <= th[3] and
                th[4] <= B <= th[5]):
            return color_name
    return "unknown"


def validate_victims(colors):
    total_points = 0
    for color in (colors):
        if color == "unknown": return None
        total_points += color_values[color]
    return [total_points, 0 <= total_points <= 2]


while True:
    img = sensor.snapshot()

    # Image center
    img_cx = img.width() // 2
    img_cy = img.height() // 2

    # Image processing
    img_binary = img.copy()
    img_binary.binary([thresholds["yellow"]])

    circles = (
        img_binary.find_circles(
            threshold=4000,
            r_min=50,
            r_max=95,
            x_margin=35,
            y_margin=35,
            r_margin=12
        )
        +
        img.find_circles(
            threshold=4000,
            r_min=50,
            r_max=95,
            x_margin=35,
            y_margin=35,
            r_margin=12
        )
    )

    if circles:
        c = max(circles, key=lambda c: c.r())

        cx = c.x()
        cy = c.y()
        cr = c.r()

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
                img.draw_circle(x, y, 3, color=(255, 0, 0))  # Drawing

                votes[sample_color] += 1

            colors.append(max(votes, key=votes.get))
        # Debug draw
        img.draw_circle((cx, cy, cr), color=(255, 0, 0))
        img.draw_cross(cx, cy, color=(255, 255, 0))

        print(colors)
        print(validate_victims(colors))
        colors = []

