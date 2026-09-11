#pragma once
#include <Arduino.h>

class EspLed {

  public:
    void setPin(uint8_t new_pin);
    void blinkLed(uint8_t, int);

  private:
    uint8_t _LED_PIN;

};