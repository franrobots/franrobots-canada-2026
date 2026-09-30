#include <ESP32Servo.h> //

#define SERVO_PIN 5

#define KIT_CENTER 90
#define KIT_LEFT 150
#define KIT_RIGHT 30

Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
  servo.write(KIT_CENTER);
}

void loop() {
  delay(5000);
  for (byte i = 0; i < 8; i++) {
    release_kits(1, true);
    delay(1500);
    release_kits(1, false);
    delay(1500);
  }
}

void shakeServo(int actualPoint, int shakes, int timeShake, int degrees) {
  for (byte i = 0; i < shakes; i++) {
    servo.write(constrain(actualPoint + degrees, 0, 180));
    delay(timeShake);

    servo.write(constrain(actualPoint - degrees, 0, 180));
    delay(timeShake);
  }

  // Back to the original point
  servo.write(actualPoint);
  delay(timeShake);
}

void dropServoKit(int kits, int time, bool shake, bool toLeft) {

  const uint8_t side = toLeft ? KIT_RIGHT : KIT_LEFT;
  
  for(byte i = 0; i < kits; i++) {
    servo.write(side);
    delay(time);

    if (shake) shakeServo(side, 30, 60, 5);

    servo.write(KIT_CENTER);
    delay(time);
  }
}

bool release_kits(uint8_t reps, bool sideFlag) {
  dropServoKit(reps, 800, true, !sideFlag);
  return true;
}