// Motor da Frente - Esquerda - 0
#define FORWARD_0 2
#define BACK_0 3
#define LEFT_MOTOR_1_0 25
#define LEFT_MOTOR_2_0 26
// Motor de Trás - Esquerda - 1
#define FORWARD_1 10
#define BACK_1 11
#define LEFT_MOTOR_1_1 33
#define LEFT_MOTOR_2_1 32 
// Motor de Trás - Direita - 2
#define FORWARD_2 4   //4
#define BACK_2 5      //5
#define RIGHT_MOTOR_1_2 16 
#define RIGHT_MOTOR_2_2 17
// Motor da Frente - Direita - 3
#define FORWARD_3 6   //6
#define BACK_3 7      //7
#define RIGHT_MOTOR_1_3 27
#define RIGHT_MOTOR_2_3 12
// Velocity to control motors
#define MIN_PWM 100
#define MAX_PWM 255
#define TURN_SPEED_DEFAULT 230

// ----------- Encoder and Motor -------------- 
// const uint8_t motor_length = 8;
// const uint8_t motor_vector[motor_length] = { FORWARD_0, BACK_0, FORWARD_1, BACK_1, FORWARD_2, BACK_2, FORWARD_3, BACK_3 };


void setup() {
  ledcSetup(FORWARD_0, 20000, 8);
  ledcSetup(BACK_0, 20000, 8);
  ledcSetup(FORWARD_1, 20000, 8);
  ledcSetup(BACK_1, 20000, 8);
  ledcSetup(FORWARD_2, 20000, 8);
  ledcSetup(BACK_2, 20000, 8);
  ledcSetup(FORWARD_3, 20000, 8);
  ledcSetup(BACK_3, 20000, 8);
  ledcAttachPin(LEFT_MOTOR_1_0, FORWARD_0);
  ledcAttachPin(LEFT_MOTOR_2_0, BACK_0);
  ledcAttachPin(LEFT_MOTOR_1_1, FORWARD_1);
  ledcAttachPin(LEFT_MOTOR_2_1, BACK_1);
  ledcAttachPin(RIGHT_MOTOR_1_2, FORWARD_2);
  ledcAttachPin(RIGHT_MOTOR_2_2, BACK_2);
  ledcAttachPin(RIGHT_MOTOR_1_3, FORWARD_3);
  ledcAttachPin(RIGHT_MOTOR_2_3, BACK_3);
  delay(100);
  Serial.print("Pronto para teste");
}

void analog_write(uint8_t channel, uint8_t value) {
  ledcWrite(channel, value < 255 ? value : 255);
}

void loop() {
  // moveTank(255, 255, true);
  analog_write(BACK_0, 0); // 26 certo | Frente esquerda
  analog_write(BACK_1, 0); // 32 certo | Trás esquerda
  analog_write(BACK_2, 0); // 17 certo | Trás direita
  analog_write(BACK_3, 0); // 12 certo | Frente direita
  analog_write(FORWARD_0, 255); // 25 errado | parado | Frente esquerda
  analog_write(FORWARD_1, 0); // 33 certo | Trás esquerda
  analog_write(FORWARD_2, 0); // 16 certo | Trás direita
  analog_write(FORWARD_3, 0); // 27 certo | Frente direita
}

int16_t motorValueCorrection(int value) {
  return (abs(value) < MIN_PWM) ? -2 * MIN_PWM + value : value;
}

void moveTank(int left_value, int right_value, bool correctionFlag) {
  if (correctionFlag) {
    left_value = motorValueCorrection(left_value);
    right_value = motorValueCorrection(right_value);
  }
  if (left_value < 0) {
    analog_write(BACK_0, 0); // 0 → 2 → troca com 3 → vira 1
    analog_write(BACK_1, 0); // 1 → 3
    analog_write(FORWARD_0, min(abs(left_value), MAX_PWM));
    analog_write(FORWARD_1, min(abs(left_value), MAX_PWM));
  } else {
    analog_write(BACK_0, min(abs(left_value), MAX_PWM));
    analog_write(BACK_1, min(abs(left_value), MAX_PWM));
    analog_write(FORWARD_0, 0);
    analog_write(FORWARD_1, 0);
  }
  // Motores da direita (motores 2 → 0, 3 → 2)
  if (right_value < 0) {
    analog_write(BACK_2, 0); // 2 → 0
    analog_write(BACK_3, 0); // 3 → 1 → troca com 0 → vira 2
    analog_write(FORWARD_2, min(abs(right_value), MAX_PWM));
    analog_write(FORWARD_3, min(abs(right_value), MAX_PWM));
  } else {
    analog_write(BACK_2, min(abs(right_value), MAX_PWM));
    analog_write(BACK_3, min(abs(right_value), MAX_PWM));
    analog_write(FORWARD_2, 0);
    analog_write(FORWARD_3, 0);
  }
}