#pragma once
#include <Arduino.h>
#include <Wire.h>

class OpenMv {

  public:
  
    bool begin(int, int, uint32_t);
    void setAddress(uint8_t new_addr) { _addr = new_addr; }
    void testI2C();

  private:
  
    uint8_t _addr;

};