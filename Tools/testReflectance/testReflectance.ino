#include <Arduino.h>

const uint8_t SENSOR_C9 = 35;
const uint8_t SENSOR_R  = 34;
const uint8_t SENSOR_G  = 36;
const uint8_t SENSOR_B  = 39;

void setup()
{
    Serial.begin(115200);

    analogReadResolution(10);

    pinMode(SENSOR_C9, INPUT);
    pinMode(SENSOR_R, INPUT);
    pinMode(SENSOR_G, INPUT);
    pinMode(SENSOR_B, INPUT);

    Serial.println("Teste da placa de refletancia");
}

void loop()
{
    int c9 = analogRead(SENSOR_C9);
    int r  = analogRead(SENSOR_R);
    int g  = analogRead(SENSOR_G);
    int b  = analogRead(SENSOR_B);

    Serial.print("C9: ");
    Serial.print(c9);

    Serial.print(" | R: ");
    Serial.print(r);

    Serial.print(" | G: ");
    Serial.print(g);

    Serial.print(" | B: ");
    Serial.println(b);

    delay(200);
}