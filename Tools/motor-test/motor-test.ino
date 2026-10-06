
// Motor da Frente - Esquerda - 0
#define FORWARD_0 11
#define BACK_0 10
#define LEFT_MOTOR_1_0 32
#define LEFT_MOTOR_2_0 33 

// ----------- Encoder and Motor -------------- 
const uint8_t motor_length = 8;
const uint8_t motor_vector[motor_length] = { FORWARD_0, BACK_0, FORWARD_1, BACK_1, FORWARD_2, BACK_2, FORWARD_3, BACK_3 };


void setup() {
  
  analogReadResolution(10);
  ledcSetup(FORWARD_0, 5000, 8);
  ledcSetup(BACK_0, 5000, 8);
  ledcSetup(FORWARD_1, 5000, 8);
  ledcSetup(BACK_1, 5000, 8);
  ledcSetup(FORWARD_2, 5000, 8);
  ledcSetup(BACK_2, 5000, 8);
  ledcSetup(FORWARD_3, 5000, 8);
  ledcSetup(BACK_3, 5000, 8);
  ledcAttachPin(LEFT_MOTOR_1_0, FORWARD_0);
  ledcAttachPin(LEFT_MOTOR_2_0, BACK_0);
  ledcAttachPin(LEFT_MOTOR_1_1, FORWARD_1);
  ledcAttachPin(LEFT_MOTOR_2_1, BACK_1);
  ledcAttachPin(RIGHT_MOTOR_1_2, FORWARD_2);
  ledcAttachPin(RIGHT_MOTOR_2_2, BACK_2);
  ledcAttachPin(RIGHT_MOTOR_1_3, FORWARD_3);
  ledcAttachPin(RIGHT_MOTOR_2_3, BACK_3);
  Serial.println("Setup ready");
}

void analog_write(uint8_t channel, uint8_t value) {
  ledcWrite(channel, value < 255 ? value : 255);
}

void loop() {
    analog_write(BACK_0, 0);
    analog_write(BACK_1, 0);
    analog_write(FORWARD_0, min(150, 255));
    analog_write(FORWARD_1, min(150, 255));
    analog_write(BACK_2, 0);
    analog_write(BACK_3, 0);
    analog_write(FORWARD_2, min(150, 255));
    analog_write(FORWARD_3, min(150, 255));

}
