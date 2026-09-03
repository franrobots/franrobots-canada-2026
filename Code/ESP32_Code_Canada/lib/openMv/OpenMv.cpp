#include <Arduino.h>
#include <Wire.h>
#include "OpenMv.h"

/// @brief 
/// @param sda 
/// @param scl 
/// @param frequency 
/// @return 
bool OpenMv::begin(int sda, int scl, uint32_t frequency) {
  Wire.begin(sda, scl, frequency);
  return true;
}

bool OpenMv::getVictimDebug(uint8_t side){
  // Sends the signal to OpenMv
  Wire.beginTransmission(side);
  Wire.write(0x00);
  uint8_t error = Wire.endTransmission();

  if (error != 0) {
      Serial.print("Error to send signal. Code: ");
      Serial.println(error);
      delay(1000);
      return false;
  }

  Serial.println("Command 0x00 sent!");

  // Request 2 bytes
  int received = Wire.requestFrom(side, (uint8_t)2);

  if (received == 2) {
    uint8_t result = Wire.read();
    uint8_t confidence = Wire.read();

    Serial.println("Response recieved!");

    Serial.print("Result: ");
    Serial.println(result);

    Serial.print("Confidence: ");
    Serial.print(confidence);
    Serial.println("%");

    // Interprets the result
    if (result == 0) {
      Serial.println("No victims found.");
      return false;
    } else {
      Serial.println("VICTIM FOUND!");

      Serial.print("Result: ");
      Serial.println(result);

      Serial.print("Confidence: ");
      Serial.print(confidence);
      Serial.println("%");

      return true;
    }

  } else {
    Serial.print("Error: waiting for 2 bytes, received ");
    Serial.println(received);
    return false;
  }

  delay(2000);
  
}


/// @brief 
/// @param side 
/// @return [value, confidence, isTrue]
VictimResult OpenMv::getVictim(uint8_t side){
  // Sends the signal to OpenMv
  Wire.beginTransmission(side);
  Wire.write(0x00);
  uint8_t error = Wire.endTransmission();

  if (error != 0) {
      Serial.print("Error to send signal. Code: ");
      Serial.println(error);
      delay(1000);
      return {0, 0, false};
  }

  int received = Wire.requestFrom(side, (uint8_t)2);

  if (received == 2) {
    uint8_t value = Wire.read();
    uint8_t confidence = Wire.read();

    if (value <= 2 && confidence > _MIN_CONFIDENCE) {
      return {value, confidence, true};
    }

    return {0, 0, false};

  } else {
    return {0, 0, false};
  }

}

void OpenMv::pingI2C(uint8_t addr) {
  Serial.println();
  Serial.println("Openning transmission OpenMV...");

  Wire.beginTransmission(addr);
  Serial.println("Transmission successfully Open");

  Serial.println();
  Serial.println("Sending signal...");
  Wire.write(0x00);

  uint8_t error = Wire.endTransmission();

  if (error != 0) {

      Serial.print("Error sending signal. Code: ");
      Serial.println(error);

      delay(1000);

      return;
  }

  Serial.println("Signal sent successfully.");
  Serial.println();

  // Request a signal
  Serial.println("Requesting signal...");
  int received = Wire.requestFrom(addr, (uint8_t)1);

  Serial.print("Bytes receiveds: ");
  Serial.println(received);

  if (received > 0) {

    uint8_t result = Wire.read();

    Serial.println("Response received successfuly!");

    Serial.print("Result: ");
    Serial.println(result);

  } else {
    Serial.println("Error to receive signal.");
  }

  delay(2000);

}