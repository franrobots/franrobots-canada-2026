#include <Arduino.h>
#include "ServoKit.h"

bool ServoKit::begin(int SERVO_PIN) {
  _attached = _servo.attach(SERVO_PIN);
  if (_attached) centerServo();
  return _attached;
}

void ServoKit::centerServo() {
  _servo.write(_mid);
}

void ServoKit::testServoCicle(int timeSide, int timeMid, bool shake) {
  Serial.println(_left);
  _servo.write(_left);
  delay(timeSide);

  if (shake) shakeServo(_left, 30, 60, 5);

  Serial.println(_mid);
  _servo.write(_mid);
  delay(timeMid);

  Serial.println(_right);
  _servo.write(_right);
  delay(timeSide);

  if (shake) shakeServo(_right, 30, 60, 5);

  Serial.println(_mid);
  _servo.write(_mid);
  delay(timeMid);
}

void ServoKit::shakeServo(int actualPoint, int shakes, int timeShake, int degrees) {
  for (byte i = 0; i < shakes; i++) {
    _servo.write(constrain(actualPoint + degrees, 0, 180));
    delay(timeShake);

    _servo.write(constrain(actualPoint - degrees, 0, 180));
    delay(timeShake);
  }

  // Volta exatamente ao ponto inicial
  _servo.write(actualPoint);
  delay(timeShake);
}

void ServoKit::dropServoKit(int kits, int time, bool shake, bool toLeft) {

  const int side = toLeft ? _mid : _right;
  
  for(byte i = 0; i < kits; i++) {
    Serial.println(side);
    _servo.write(side);
    delay(time);

    if (shake) shakeServo(_left, 30, 60, 5);

    Serial.println(_mid);
    _servo.write(_mid);
    if (kits > 1) delay(time);
  }
}
