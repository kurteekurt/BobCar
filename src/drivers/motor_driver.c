/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Jake Klopukh
 * Student ID:: 922783729
 * Project:: Line Following Car Term Project
 *
 * File:: motor_driver.h
 *
 * Description:: Implementation of the motor driver. Implements
 * functions that start up the motors, change their speed, direction,
 * and a function that stops them.
 **************************************************************/

#include "drivers/motor_driver.h"

// Start up the two motors
void motorInit() {
  PCA9685_Init(0x40);
  PCA9685_SetPWMFreq(100);

  // Set the motor directions to forward
  motorSetDirection(RIGHT_MOTOR, FORWARD);
  motorSetDirection(LEFT_MOTOR, FORWARD);
}

// Set the chosen motor to move at a given speen between 0-100
void motorMove(Motor motor, int speed) {
  if (speed < 0) {
    motorSetDirection(motor, BACKWARD);
    speed = -speed;
  } else {
    motorSetDirection(motor, FORWARD);
  }

  if (motor == RIGHT_MOTOR) {
    PCA9685_SetPwmDutyCycle(PWMA, speed);
  } else {
    PCA9685_SetPwmDutyCycle(PWMB, speed);
  }
}

// Sets the direction that the motors will turn
void motorSetDirection(Motor motor, Direction direction) {
  // Motor A and B move in opposite directions due to their orientation
  if (direction == BACKWARD) {
    if (motor == RIGHT_MOTOR) {
      PCA9685_SetLevel(AIN1, 0);
      PCA9685_SetLevel(AIN2, 1);
    } else {
      PCA9685_SetLevel(BIN1, 1);
      PCA9685_SetLevel(BIN2, 0);
    }
  } else {
    if (motor == RIGHT_MOTOR) {
      PCA9685_SetLevel(AIN1, 1);
      PCA9685_SetLevel(AIN2, 0);
    } else {
      PCA9685_SetLevel(BIN1, 0);
      PCA9685_SetLevel(BIN2, 1);
    }
  }
}

// Stop both motors from movement.
void motorStop() {
  PCA9685_SetPwmDutyCycle(PWMA, 0);
  PCA9685_SetPwmDutyCycle(PWMB, 0);
}
