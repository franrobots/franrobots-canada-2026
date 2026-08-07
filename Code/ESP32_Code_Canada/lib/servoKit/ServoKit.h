#pragma once
#include <Arduino.h>
#include "ESP32Servo.h"

class ServoKit {

  public:
    bool begin(int);
    void testServoCicle(int, int, bool);
    void dropServoKit(int, int, bool, bool);

  private:
    Servo _servo;

    int _left = 150;
    int _mid = 90;
    int _right = 30;

    bool _attached = false;
    void centerServo();
    void shakeServo(int, int, int, int);

};