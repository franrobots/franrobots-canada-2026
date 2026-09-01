import pyb
import time

I2C_ADDR = 0x12

bus = pyb.I2C(2, pyb.I2C.SLAVE, addr=I2C_ADDR)

buffer = bytearray([3, 87])

print("================================")
print("OPENMV - TESTE I2C")
print("Endereco:", hex(I2C_ADDR))
print("================================")

while True:

    try:

        cmd = bus.recv(1, timeout=1000)

        if cmd:

            print("[I2C] Comando recebido:", hex(cmd[0]))

            if cmd[0] == 0x00:

                bus.send(buffer)

                print(
                    "[I2C] Enviado:",
                    buffer[0],
                    buffer[1]
                )

    except Exception as e:

        pass
