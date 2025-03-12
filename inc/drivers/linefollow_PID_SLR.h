/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Sergio Licardie
 * Student ID:: 922739516
 * Project:: Line Following Car Term Project
 *
 * File:: linefollow_PID_SLR.h
 *
 * Description:: h file for first attempt at PID for LineFollowing
 * Car
 *
 **************************************************************/
#ifndef INC_LINEFOLLOW_H
#define INC_LINEFOLLOW_H

#include <pthread.h>

// PID Control Values
typedef struct {
  float gain_p;
  float gain_i;
  float gain_d;
  int lfSpeed;
} ControlValues;

typedef struct {
  ControlValues *ctrl_values;
  pthread_mutex_t *mutex;
} LinefollowPIDArg;

// initialize PID protocol
void *initializePID(void *args);

// shutdown PID (does not currently do anything)
void shutdownPID();

// testing math in PID functions with a testing function
// void dryTestingPID();

#endif