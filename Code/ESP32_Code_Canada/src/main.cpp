#include <Arduino.h>
#include <Wire.h>
#include "ServoKit.h"
#include "OpenMv.h"

ServoKit servoKit;
OpenMv openMv;

#define SERVO_PIN 5
#define I2C_SDA 21
#define I2C_SCL 22

void setup() {
  Serial.begin(115200);
  openMv.begin(I2C_SDA, I2C_SCL, 100000);
  openMv.setAddress(0x12);

  delay(100);
}

void loop() {
  openMv.testI2C();
}