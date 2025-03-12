/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Sergio Licardie
 * Student ID:: 922739516
 * Project:: Line Following Car Term Project
 *
 * File:: line_sensors.c
 *
 * Description:: Contains threaded functions for reading the line sensor
 * inputs for the car
 *
 **************************************************************/

#include "sensors/line_sensors.h"
#define OUTER_LEFT 23
#define INNER_LEFT 27
#define MIDDLE 22
#define INNER_RIGHT 17
#define OUTER_RIGHT 24
#define ARCH_LEFT 5
#define ARCH_RIGHT 25

volatile int *sensor_array;

const int SENSOR_PINS[NUM_SENSORS] = {ARCH_LEFT, OUTER_LEFT,  INNER_LEFT,
                                      MIDDLE,    INNER_RIGHT, OUTER_RIGHT,
                                      ARCH_RIGHT};

void *lineSensorRead(void *arg) {
  (void)arg;
  int timeout_line = 0;

  while (1) {
    if (timeout_line >= 10000) {
      printf("timed out\n");
      pthread_exit(NULL);
      return 0;
    }

    for (int i = 0; i < NUM_SENSORS; i++) {
      sensor_array[i] = ~digitalRead(SENSOR_PINS[i]) & 1;
    }
  }
  return 0;
}

int allSensorsZero() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor_array[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int allSensorsOne() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor_array[i] != 1) {
      return 0;
    }
  }
  return 1;
}

int initializeLineSensors() {
  sensor_array = calloc(NUM_SENSORS, sizeof(int));

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
    pullUpDnControl(SENSOR_PINS[i], PUD_UP);
  }

  return 0;
}

int shutdownLineSensors() { return 0; }