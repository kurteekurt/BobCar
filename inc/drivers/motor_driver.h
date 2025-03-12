/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Jake Klopukh
 * Student ID:: 922783729
 * Project:: Line Following Car Term Project
 *
 * File:: motor_driver.h
 *
 * Description:: Header file for motor control. Defines a function
 * for starting up the motors, controlling speeds for the motors,
 * the directions of the motors, and stopping them.
 **************************************************************/
#ifndef INC_MOTORDRIVER_H
#define INC_MOTORDRIVER_H

#include "waveshare/DEV_Config.h"
#include "waveshare/PCA9685.h"

// Channels 1-3 for Motor A
#define PWMA PCA_CHANNEL_0
#define AIN1 PCA_CHANNEL_1
#define AIN2 PCA_CHANNEL_2
#define PWMB PCA_CHANNEL_5
#define BIN1 PCA_CHANNEL_3
#define BIN2 PCA_CHANNEL_4

typedef enum { RIGHT_MOTOR, LEFT_MOTOR } Motor;
typedef enum { FORWARD, BACKWARD } Direction;

void motorInit(void);
void motorMove(Motor motor, int speed);
void motorSetDirection(Motor motor, Direction direction);
void motorStop();

#endif
