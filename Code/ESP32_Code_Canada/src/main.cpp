#include <Arduino.h>
#include <Wire.h>
#include "ServoKit.h"
#include "OpenMv.h"

ServoKit servoKit;
OpenMv openMv;

// Pins and Address
#define SERVO_PIN 5
#define I2C_SDA 21
#define I2C_SCL 22
#define left_cam 0x12
#define right_cam 0x14

void setup() {
  Serial.begin(115200);
  openMv.begin(I2C_SDA, I2C_SCL, 100000);

  delay(100);
}

void loop() {
  // Query the victim
  VictimResult result = openMv.getVictim(left_cam);

  if (result.isTrue) {
    servoKit.dropServoKit(result.value, 800, true, true);
  }
  else {
    result = openMv.getVictim(right_cam);

    if (result.isTrue) {
      servoKit.dropServoKit(result.value, 800, true, false);
    }
  }

}