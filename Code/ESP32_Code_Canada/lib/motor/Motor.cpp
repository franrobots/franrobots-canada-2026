#include <Arduino.h>

#include "Motor.h"
#include "config.h"

bool Motor::begin()
{

  const bool frontLeftMotor1 =
      ledcAttach(FRONT_LEFT_MOTOR_1, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool frontLeftMotor2 =
      ledcAttach(FRONT_LEFT_MOTOR_2, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool rearLeftMotor1 =
      ledcAttach(REAR_LEFT_MOTOR_1, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool rearLeftMotor2 =
      ledcAttach(REAR_LEFT_MOTOR_2, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool rearRightMotor1 =
      ledcAttach(REAR_RIGHT_MOTOR_1, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool rearRightMotor2 =
      ledcAttach(REAR_RIGHT_MOTOR_2, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool frontRightMotor1 =
      ledcAttach(FRONT_RIGHT_MOTOR_1, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  const bool frontRightMotor2 =
      ledcAttach(FRONT_RIGHT_MOTOR_2, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);

  stop();

  return frontLeftMotor1 &&
         frontLeftMotor2 &&
         rearLeftMotor1 &&
         rearLeftMotor2 &&
         rearRightMotor1 &&
         rearRightMotor2 &&
         frontRightMotor1 &&
         frontRightMotor2;
}

uint16_t Motor::speedToDuty(int16_t speed)
{
    speed = abs(speed);

    if (speed > MOTOR_MAX_DUTY)
        speed = MOTOR_MAX_DUTY;

    return static_cast<uint16_t>(speed);
}

void Motor::setMotor(
    uint8_t pin1,
    uint8_t pin2,
    int16_t speed
)
{
    uint16_t duty = speedToDuty(speed);

    if (speed > 0)
    {
        // Uma direção
        ledcWrite(pin1, duty);
        ledcWrite(pin2, 0);
    }
    else if (speed < 0)
    {
        // Direção oposta
        ledcWrite(pin1, 0);
        ledcWrite(pin2, duty);
    }
    else
    {
        // Parado
        ledcWrite(pin1, 0);
        ledcWrite(pin2, 0);
    }
}

void Motor::moveTank(
    int16_t leftSpeed,
    int16_t rightSpeed
)
{
    // Lado esquerdo
    setMotor(
        FRONT_LEFT_MOTOR_1,
        FRONT_LEFT_MOTOR_2,
        leftSpeed
    );

    setMotor(
        REAR_LEFT_MOTOR_1,
        REAR_LEFT_MOTOR_2,
        leftSpeed
    );

    // Lado direito
    setMotor(
        REAR_RIGHT_MOTOR_1,
        REAR_RIGHT_MOTOR_2,
        rightSpeed
    );

    setMotor(
        FRONT_RIGHT_MOTOR_1,
        FRONT_RIGHT_MOTOR_2,
        rightSpeed
    );
}

void Motor::turnLeft(int16_t speed)
{
    moveTank(-speed, speed);
}

void Motor::turnRight(int16_t speed)
{
    moveTank(speed, -speed);
}

void Motor::stop()
{
    moveTank(0, 0);
}

// void Motor::pdcontrol(int16_t, int16_t, float, float, uint8_t) {
//     // Needs BNO
// }
