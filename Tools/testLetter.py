import sensor
import ml
import time
import omv

sensor.reset()

sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)
sensor.set_windowing((120, 120))

# Durante o diagnóstico, não use espelhamento
sensor.set_hmirror(False)
sensor.set_vflip(False)

sensor.skip_frames(time=2000)

net = ml.Model("trained.tflite")

labels = [line.strip() for line in open("labels.txt")]

print("================================")
print("Firmware:", omv.version_string())
print("Board:", omv.board_type())
print("Labels:", labels)
print("Input shape:", net.input_shape)
print("Input dtype:", net.input_dtype)
print("Input scale:", net.input_scale)
print("Input zero:", net.input_zero_point)
print("Output shape:", net.output_shape)
print("Output dtype:", net.output_dtype)
print("================================")

clock = time.clock()

while True:
    clock.tick()

    img = sensor.snapshot()

    prediction = net.predict([img])[0].flatten().tolist()

    ranked = sorted(
        zip(labels, prediction),
        key=lambda x: x[1],
        reverse=True
    )

    print("----")
    for label, confidence in ranked:
        print("{} = {:.4f}".format(label, confidence))

    print("FPS:", clock.fps())
