#pragma once
#include <Arduino.h>
#include <Wire.h>

struct VictimResult {
  uint8_t value;
  uint8_t confidence;
  bool isTrue;
};

class OpenMv {

  public:
  
    bool begin(int, int, uint32_t);
    // void setAddress(uint8_t new_addr) { _addr = new_addr; }
    bool getVictimDebug(uint8_t);
    VictimResult getVictim(uint8_t);
    void pingI2C(uint8_t);

  private:
  
    // uint8_t _addr;
    static constexpr uint8_t _MIN_CONFIDENCE = 87;

};