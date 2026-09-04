#include <Arduino.h>
#include "config.h"

#include <Wire.h>
#include "ServoKit.h"
#include "OpenMv.h"

ServoKit servoKit;
OpenMv openMv;

// Functions declarations
void blinkLed(uint8_t);

void setup() {
  Serial.begin(115200);
  openMv.begin(I2C_SDA, I2C_SCL, 100000);
  servoKit.begin(SERVO_PIN);
  servoKit.dropServoKit(2, 800, false, true);
  pinMode(LED_PIN, OUTPUT);
  delay(100);
}

void loop() {
  // Query the victim
  delay(1000);
  VictimResult result = openMv.getVictim(LEFT_CAM);
  Serial.println(result.value);
  Serial.println(result.confidence);
  Serial.println(result.isTrue);

  if (result.isTrue) {
    blinkLed(3);
    servoKit.dropServoKit(result.value, 800, true, true); 
  }
  else {
    result = openMv.getVictim(RIGHT_CAM);

    if (result.isTrue) {
      blinkLed(3);
      servoKit.dropServoKit(result.value, 800, true, false);
    }
  }

  // Serial.println("virando servo");
  // servoKit.dropServoKit(2, 800, true, true);

}

void blinkLed(uint8_t times) {
  for (byte i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);  
  }
}