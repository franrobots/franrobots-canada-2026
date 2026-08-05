// #include <Arduino.h>
// #include "ESP32Servo.h"

// int left = 150;
// int mid = 90;
// int right = 30;

// Servo servo;

// const int SERVO_PIN = 5;

// void setup() {
//   Serial.begin(115200);
//   servo.attach(SERVO_PIN);
//   Serial.println("Servo iniciado");
  
//   Serial.println(mid);
//   servo.write(mid);
//   delay(1000);
// }


// void oneCicle(int timeSide, int timeMid, bool shake) {
//   Serial.println(left);
//   servo.write(left);
//   delay(timeSide);

//   if (shake) shakeServo(left, 30, 60, 5);

//   Serial.println(mid);
//   servo.write(mid);
//   delay(timeMid);

//   Serial.println(right);
//   servo.write(right);
//   delay(timeSide);

//   if (shake) shakeServo(right, 30, 60, 5);

//   Serial.println(mid);
//   servo.write(mid);
//   delay(timeMid);
// }

// void shakeServo(int actualPoint, int shakes, int timeShake, int degrees) {
//   for (byte i = 0; i < shakes; i++) {
//     servo.write(constrain(actualPoint + degrees, 0, 180));
//     delay(timeShake);

//     servo.write(constrain(actualPoint - degrees, 0, 180));
//     delay(timeShake);
//   }

//   // Volta exatamente ao ponto inicial
//   servo.write(actualPoint);
//   delay(timeShake);
// }

// void loop() {
//   // for (int i = 90; i <= 270; i+=10) {
//   //  Serial.println(i);
//   //  servo.write(i);
//   //  delay(3000);
//   // }
  
//   oneCicle(300, 3000, true);
// }

// // Serial.available() > 0