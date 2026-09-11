#include <Arduino.h>
#include "EspLed.h"

void EspLed::setPin(uint8_t pin) {
  _LED_PIN = pin;
  pinMode(_LED_PIN, OUTPUT);
}

void EspLed::blinkLed(uint8_t blinks, int timeblink) {
  for (byte i = 0; i < blinks; i++) {
    digitalWrite(_LED_PIN, HIGH);
    delay(timeblink);
    digitalWrite(_LED_PIN, LOW);
    delay(timeblink);  
  }
}