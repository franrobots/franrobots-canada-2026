#pragma once
#include <Arduino.h>

class Motor {

  public:
    bool begin();
    void moveTank(int16_t leftSpeed, int16_t rightSpeed);
    void stop();

  private:
    void setMotor(uint8_t pin1, uint8_t pin2, int16_t speed);
    uint16_t speedToDuty(int16_t speed);

};