#include <Arduino.h>
#include "ServoKit.h"

ServoKit servoKit;

// int left = 150;
// int mid = 90;
// int right = 30;

const int SERVO_PIN = 5;

void setup() {
  Serial.begin(115200);
  servoKit.begin(SERVO_PIN);
  Serial.println("Servo iniciado");
  
  delay(1000);
}

void loop() {
  // for (int i = 90; i <= 270; i+=10) {
  //  Serial.println(i);
  //  servo.write(i);
  //  delay(3000);
  // }
  
  servoKit.testServoCicle(300, 3000, true);
  servoKit.dropServoKit(2, 800, true, true);
}

// Serial.available() > 0