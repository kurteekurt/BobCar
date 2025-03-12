/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Sergio Licardie
 * Student ID:: 922739516
 * Project:: Line Following Car Term Project
 *
 * File:: line_sensors.h
 *
 * Description:: Header file for the line_sensors.c file.
 * Use the lineSensor struct to pass PIN and a place to store
 * the results. sign it with VALID define for pthread void pointer
 * validation. pass it into lineSensorRead after calling wiringPiSetupGpio()
 *
 **************************************************************/
#ifndef INC_LINESENSORS_H
#define INC_LINESENSORS_H

#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

#define HIGH 1
#define LOW 0

#define NUM_SENSORS 7

extern volatile int *sensor_array;

int initializeLineSensors();

void *lineSensorRead(void *sensor_info);

int allSensorsZero();
int allSensorsOne();

int shutdownLineSensors();

#endif