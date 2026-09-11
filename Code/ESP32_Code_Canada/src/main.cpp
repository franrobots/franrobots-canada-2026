#include <Arduino.h>
#include "config.h"

#include "ServoKit.h"
#include "OpenMv.h"
#include "EspLed.h"

ServoKit servoKit;
OpenMv openMv;
EspLed espLed;

// Functions declarations
void victimCicle();

void setup() {
  Serial.begin(115200);
  openMv.begin(I2C_SDA, I2C_SCL, 100000);
  servoKit.begin(SERVO_PIN);
  espLed.setPin(LED_PIN);
  delay(100);
  Serial.println("God bless the round!");
}

void loop() {
  espLed.blinkLed(5, 800);
  victimCicle();
}

void victimCicle() {
    // Query the victim
  delay(1000);
  VictimResult result = openMv.getVictim(LEFT_CAM);
  Serial.println(result.value);
  Serial.println(result.confidence);
  Serial.println(result.isTrue);

  if (result.isTrue) {
    espLed.blinkLed(5, 800);
    servoKit.dropServoKit(result.value, 800, true, true); 
  }
  else {
    result = openMv.getVictim(RIGHT_CAM);

    if (result.isTrue) {
      espLed.blinkLed(5, 800);
      servoKit.dropServoKit(result.value, 800, true, false);
    }
  }
}