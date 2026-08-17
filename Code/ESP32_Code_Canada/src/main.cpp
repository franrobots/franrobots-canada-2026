#include <Arduino.h>
#include "ServoKit.h"

ServoKit servoKit;

const int SERVO_PIN = 5;

void setup() {
  Serial.begin(115200);
  servoKit.begin(SERVO_PIN);
  Serial.println("Servo iniciado");
  
  delay(1000);
}

void loop() {
  // servoKit.dropServoKit(2, 800, true, true);
  // servoKit.testServoCicle(300, 3000, true);
  servoKit.testServoAngle(false);
  servoKit.testServoAngle(true);
}

// Serial.available() > 0