#include <Arduino.h>
#include "ServoKit.h"

// ---------- Servo initialization ----------

/// @param SERVO_PIN 
bool ServoKit::begin(int SERVO_PIN) {
  _attached = _servo.attach(SERVO_PIN);
  if (_attached) centerServo();
  return _attached;
}

void ServoKit::centerServo() {
  _servo.write(_mid);
}

// ---------- Servo tests----------

/// @brief 
/// Rotate the servo to both sides, releasing the kits alternately.
/// @param timeSide 
/// @param timeMid 
/// @param shake 
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

/// @brief 
/// Makes the servo oscillate, moving [int degrees] above and below the [int actualPoint].
/// @param actualPoint 
/// @param shakes 
/// @param timeShake 
/// @param degrees 
void ServoKit::shakeServo(int actualPoint, int shakes, int timeShake, int degrees) {
  for (byte i = 0; i < shakes; i++) {
    _servo.write(constrain(actualPoint + degrees, 0, 180));
    delay(timeShake);

    _servo.write(constrain(actualPoint - degrees, 0, 180));
    delay(timeShake);
  }

  // Back to the original point
  _servo.write(actualPoint);
  delay(timeShake);
}

/// @brief
/// Under development
/// @param toLeft 
void ServoKit::testServoAngle(bool toLeft) {
  if (toLeft) {
    for (byte i = 90; i <= 270; i+=10) {
      Serial.println(i);
      _servo.write(i);
      delay(2500);
    }
  } else {
    for (byte i = 90; i >= 10; i-=10) {
      Serial.println(i);
      _servo.write(i);
      delay(2500);
    }
  }
}

// ---------- Main functions ----------

/// @brief 
/// Release the kit on the chosen side.
/// @param kits 
/// @param time 
/// @param shake 
/// @param toLeft 
void ServoKit::dropServoKit(int kits, int time, bool shake, bool toLeft) {

  const int side = toLeft ? _right : _left;
  
  for(byte i = 0; i < kits; i++) {
    _servo.write(side);
    delay(time);

    if (shake) shakeServo(side, 30, 60, 5);

    _servo.write(_mid);
    delay(time);
  }
}

