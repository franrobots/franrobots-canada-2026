#include <Adafruit_NeoPixel.h>

#define LEDS_PIN 23
#define N_LEDS 3

void beginLed();
void blink_led();
void led_clear();

Adafruit_NeoPixel led = Adafruit_NeoPixel(N_LEDS, LEDS_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  led.begin();
  led_clear();
  beginLed();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void beginLed() {
  long color = 0xFFFFFF; // Branco
  led.setPixelColor(0, color); // LED 7
  led.setPixelColor(1, color); // LED 7
  led.setPixelColor(2, color); // LED 8
  led.setPixelColor(3, color); // LED 8
  led.setPixelColor(4, color); // LED 8
  led.setPixelColor(5, color); // LED 8
  // led.setPixelColor(6, color); // LED 8
  // led.setPixelColor(7, color); // LED 8
  // led.setPixelColor(8, color); // LED 8
  // led.setPixelColor(9, color); // LED 8
  // led.setPixelColor(10, color); // LED 8
  // led.setPixelColor(11, color); // LED 8
  led.show();
}


// ------------------------- LED blink --------------------------- // 
void blink_led(uint8_t repeticoes, uint8_t typeColor, bool side) {
  long color;
  int8_t ledToBlink[2];

  // Define os LEDs a piscar com base no lado
  if (side) { // lado direito
    ledToBlink[0] = 3;
    ledToBlink[1] = 4;
  } else {     // lado esquerdo
    ledToBlink[0] = 0;
    ledToBlink[1] = 1;
  }
  // Define a cor correspondente
  if (typeColor == 0) color = 0x00FF00; // Verde 
  else if (typeColor == 1) color = 0xFFFF00; // Amarelo
  else if (typeColor == 2) color = 0xFF0000; // Vermelho
  else if (typeColor == 3) color = 0x0000FF; // Azul
  else if (typeColor == 4) color = 0xFFFFFF; // Branco
  else color = 0x000000; // Cor padrão (apagado) se tipo inválido

  // Piscar os LEDs
  for (uint8_t i = 0; i < repeticoes; i++) {
    if(color == 0xFFFFFF || color == 0x0000FF){
    led.setPixelColor(0, color);
    led.setPixelColor(1, color);
    led.setPixelColor(2, color);
    led.setPixelColor(3, color);
    led.setPixelColor(4, color);
    led.setPixelColor(5, color);
    // led.setPixelColor(6, 0xFFFFFF);
    // led.setPixelColor(7, 0xFFFFFF);
    // led.setPixelColor(8, 0xFFFFFF);
    // led.setPixelColor(9, 0xFFFFFF);
    // led.setPixelColor(10, 0xFFFFFF);
    led.show();
    vTaskDelay(pdMS_TO_TICKS(500));
    led_clear();
    vTaskDelay(pdMS_TO_TICKS(500));
    }else{
    led.setPixelColor(ledToBlink[0], color);
    led.setPixelColor(ledToBlink[1], color);
    led.show();
    vTaskDelay(pdMS_TO_TICKS(500));
    led_clear();
    vTaskDelay(pdMS_TO_TICKS(500));
    }
  }
    // led.setPixelColor(5, 0xFFFFFF);
    // led.setPixelColor(6, 0xFFFFFF);
    // led.setPixelColor(7, 0xFFFFFF);
    // led.setPixelColor(8, 0xFFFFFF);
    // led.setPixelColor(9, 0xFFFFFF);
    // led.setPixelColor(10, 0xFFFFFF);
}

void led_clear() {
  for (uint8_t i = 0; i < (N_LEDS); i++) led.setPixelColor(i, 0);
  led.show();
}
