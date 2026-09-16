#pragma once
#include <Arduino.h>

class Motor {

  public:
    bool begin();
    void moveTank(int16_t leftSpeed = 2457, int16_t rightSpeed = 2457);
    void turnLeft(int16_t speed = 2457);
    void turnRight(int16_t speed = 2457);
    void stop();
    // void pdcontrol(int16_t, int16_t, float, float, uint8_t);

  private:
    void setMotor(uint8_t pin1, uint8_t pin2, int16_t speed);
    uint16_t speedToDuty(int16_t speed);

};