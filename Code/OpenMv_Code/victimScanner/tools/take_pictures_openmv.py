import sensor, time, ml, uos, gc, pyb
from machine import LED

# ------------------------- Inicialização -------------------------
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_hmirror(True)
sensor.set_vflip(True)
sensor.skip_frames(time=2000)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False)

NUM_FOTOS = 10
INTERVALO_MS = 1000

while True:
    img = sensor.snapshot()

    time.sleep_ms(1000)
    print("Capturando fotos...")

    for i in range(1, NUM_FOTOS + 1):
        img = sensor.snapshot()
        nome_arquivo = "foto_%d.jpg" % i
        img.save(nome_arquivo)
        print("Foto salva:", nome_arquivo)
        time.sleep_ms(INTERVALO_MS)

    print("Captura finalizada.")

    # print("FPS:", clock.fps())
    gc.collect()
