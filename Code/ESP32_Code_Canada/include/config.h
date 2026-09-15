#pragma once
#include <Arduino.h>

// ----- General -----

constexpr uint8_t LED_PIN = 2;
constexpr uint8_t SERVO_PIN = 5;

// ----- I2C -----

constexpr uint8_t I2C_SDA = 21;
constexpr uint8_t I2C_SCL = 22;

// ----- OpenMV -----

constexpr uint8_t LEFT_CAM = 0x12;
constexpr uint8_t RIGHT_CAM = 0x14;

// ----- Motor PWM -----

constexpr uint32_t MOTOR_PWM_FREQUENCY = 20000;
constexpr uint8_t MOTOR_PWM_RESOLUTION = 12; // 0 - 4096
constexpr uint16_t MOTOR_MAX_DUTY = 4095;

// ----- Motor pins -----

// Front Left - Motor 0
constexpr uint8_t FRONT_LEFT_MOTOR_1 = 32;
constexpr uint8_t FRONT_LEFT_MOTOR_2 = 33;

// Rear Left - Motor 1
constexpr uint8_t REAR_LEFT_MOTOR_1 = 26;
constexpr uint8_t REAR_LEFT_MOTOR_2 = 25;

// Rear Right - Motor 2
constexpr uint8_t REAR_RIGHT_MOTOR_1 = 27;
constexpr uint8_t REAR_RIGHT_MOTOR_2 = 16;

// Front Right - Motor 3
constexpr uint8_t FRONT_RIGHT_MOTOR_1 = 17;
constexpr uint8_t FRONT_RIGHT_MOTOR_2 = 12;