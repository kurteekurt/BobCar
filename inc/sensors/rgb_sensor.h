/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Jake Klopukh
 * Student IDs:: 922783729
 * GitHub-Name:: jklopukh
 * Group-Name:: Bob's Builders
 * Project:: Line Following Car Term Project
 *
 * File:: rgb_sensor.h
 *
 * Description:: Contains declarations of the functions used to
 *               read the RGB sensor as well as a struct typedef
 *               for the sensor results.
 *
 **************************************************************/
#include "waveshare/TCS34725.h"
#include <stdlib.h>

typedef struct {
  int rgb;
  short R, G, B;
  double hue, saturation, value;
  char *color;
  double accuracy;
} rgb_sensor_output;

// Set up and shut down functions
int initRGBSensor();
void stopRGBSensor();

// function for getting sensor output
void getRGBInfo(rgb_sensor_output *);

void *runColorSensor(void *arg);