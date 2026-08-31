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

void OpenMv::testI2C() {
  Serial.println();
  Serial.println("Perguntando para OpenMV...");

  // ========================================================
  // 1. Envia comando 0x00
  // ========================================================

  Wire.beginTransmission(_addr);

  Wire.write(0x00);

  uint8_t error = Wire.endTransmission();

  if (error != 0) {

      Serial.print("Erro ao enviar comando. Codigo: ");
      Serial.println(error);

      delay(1000);

      return;
  }

  Serial.println("Comando enviado!");

  // ========================================================
  // 2. Solicita 2 bytes
  // ========================================================

  int received = Wire.requestFrom(_addr, (uint8_t)2);

  Serial.print("Bytes recebidos: ");
  Serial.println(received);

  if (received == 2) {

    uint8_t result = Wire.read();
    uint8_t confidence = Wire.read();

    Serial.println("Resposta recebida!");

    Serial.print("Result: ");
    Serial.println(result);

    Serial.print("Confidence: ");
    Serial.print(confidence);
    Serial.println("%");

    // ====================================================
    // 3. Interpreta resultado
    // ====================================================

    if (result == 0) {
      Serial.println("Nenhuma vitima encontrada.");
    } else {
      Serial.println("*** VITIMA ENCONTRADA! ***");

      Serial.print("Tipo da vitima: ");
      Serial.println(result);

      Serial.print("Confianca: ");
      Serial.print(confidence);
      Serial.println("%");
    }

  } else {
    Serial.print("Erro: esperava 2 bytes, recebeu ");
    Serial.println(received);
  }

  delay(2000);

}