/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Sergio Licardie
 * Student ID:: 922739516
 * Project:: Line Following Car Term Project
 *
 * File:: linefollow_PID_SLR.c
 *
 * Description:: Contains first attempt at PID for LineFollowing
 * Car
 *
 **************************************************************/

#include "drivers/linefollow_PID_SLR.h"
#include "drivers/motor_driver.h"
#include "sensors/line_sensors.h"
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

#include "core/pidMath.h"

void motorDirection(int left, int right) {
  motorMove(RIGHT_MOTOR, right);
  motorMove(LEFT_MOTOR, left);
}

void pidLine(int error_num, int *integral_val, int *previous_error,
             ControlValues *ctrl_values) {
  int base_speed = ctrl_values->lfSpeed;
  int kp = ctrl_values->gain_p;
  int ki = ctrl_values->gain_i;
  int kd = ctrl_values->gain_d;
  int proportional = error_num;
  int integral = *integral_val + error_num;
  int derivative = error_num - *previous_error;

  integral = fclamp(integral, -30, 30);

  int p_value = ((kp)*proportional);
  int i_value = (ki)*integral;
  int d_value = (kd)*derivative;

  float pid_val = p_value + i_value + d_value;
  *previous_error = error_num;

  int left_speed = base_speed + pid_val;
  int right_speed = base_speed - pid_val;

  left_speed = clamp(left_speed, 0, 90);
  right_speed = clamp(right_speed, 0, 90);

  *integral_val = integral;

  motorDirection(left_speed, right_speed);
}

int findPosition() {
  static const int WEIGHTS[] = {-7, -4, -2, 1, 2, 4, 7};

  int position = 0;
  for (int i = 0; i < NUM_SENSORS; i++) {
    position += sensor_array[i] * WEIGHTS[i];
  }

  return position;
}

int inputParsing(int base_speed, int *previous_error) {
  int position = findPosition();

  while (allSensorsZero()) {
    if (*previous_error == 0) {
      motorDirection(base_speed, 0);
    } else {
      motorDirection(0, base_speed);
    }
  }

  while (allSensorsOne()) {
    if (*previous_error > 0) {
      motorDirection(base_speed, 0);
    } else {
      motorDirection(0, base_speed);
    }
  }
  return position;
}

void *initializePID(void *args) {
  LinefollowPIDArg *arguments = (LinefollowPIDArg *)args;
  ControlValues *ctrl_values = arguments->ctrl_values;
  pthread_mutex_t *mutex = arguments->mutex;

  int base_speed = ctrl_values->lfSpeed;
  int integral = 0;
  int err = 0;
  int previous_error = 0;
  motorInit();
  motorDirection(base_speed, base_speed);

  while (1) {
    pthread_mutex_lock(mutex);
    err = inputParsing(base_speed * 1.2, &previous_error);
    pidLine(err, &integral, &previous_error, ctrl_values);
    pthread_mutex_unlock(mutex);
    usleep(1000); // Add a small delay to prevent busy-waiting
  }

  return NULL;
}

void shutdownPID() {}