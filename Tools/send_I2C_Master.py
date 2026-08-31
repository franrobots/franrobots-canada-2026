from pyb import I2C

i2c = I2C(2)                              # create on bus 2 (uninitialised)
i2c.init(I2C.CONTROLLER, addr=0x12, baudrate=100000)       # init as a peripheral with the given address

print(i2c.scan())
print(i2c.is_ready(8))

i2c.send("Send enviado", addr=8)
i2c.mem_write("mem write enviado", addr=8, memaddr=0x12)

print("mensagem enviada")

print("end")
