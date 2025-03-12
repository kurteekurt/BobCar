/**************************************************************
 * Class:: CSC-615-01 Fall 2024
 * Name:: Jake Klopukh
 * Student IDs:: 922783729
 * GitHub-Name:: jklopukh
 * Group-Name:: Bob's Builders
 * Project:: Line Following Car Term Project
 *
 * File:: rgb_sensor.c
 *
 * Description:: Implements a library which uses the TCS34725
 *               rgb sensor to get a color and a guess at which color
 *               it is. Also contains a function for a thread to run
 *               and raise signals on red and yellow.
 *
 **************************************************************/
#include "sensors/rgb_sensor.h"
#include "core/watchdog.h"
#include <math.h>
#include <signal.h>

// The max distance around a circle is 360 degrees
#define MAX_HUE_DISTANCE 360.0
// An HSV with value of under BLACK_VALUE_MAX is black
#define BLACK_VALUE_MAX 20

typedef struct {
  char *colorname;
  double hue;
} Color;

const Color COLORS[] = {{"Red", 0},    {"Yellow", 60}, {"Green", 120},
                        {"Cyan", 180}, {"Blue", 240},  {"Magenta", 300},
                        {"Red", 360}};

double getMax(double a, double b) {
  if (a > b)
    return a;
  else
    return b;
}

double getMin(double a, double b) {
  if (a < b)
    return a;
  else
    return b;
}

// Divide r, g, b by 255
// Compute cmax, cmin, difference
// Hue calculation :
// if cmax and cmin are equal, then h = 0
// if cmax equal r then compute h = (60 * ((g – b) / diff) + 360) % 360
// if cmax equal g then compute h = (60 * ((b – r) / diff) + 120) % 360
// if cmax equal b then compute h = (60 * ((r – g) / diff) + 240) % 360
// Saturation computation :
// if cmax = 0, then s = 0
// if cmax does not equal 0 then compute s = (diff/cmax)*100
// Value computation :
// v = cmax*100
void calculateHSV(rgb_sensor_output *sensor_color) {
  double r = (double)sensor_color->R / 255.0;
  double g = (double)sensor_color->G / 255.0;
  double b = (double)sensor_color->B / 255.0;

  double cmax = getMax(r, getMax(g, b));
  double cmin = getMin(r, getMin(g, b));

  double difference = cmax - cmin;

  // Calculate hue
  if (difference == 0) {
    sensor_color->hue = 0;
  } else if (cmax == r) {
    sensor_color->hue = fmod(60 * ((g - b) / difference) + 360, 360);
  } else if (cmax == g) {
    sensor_color->hue = fmod(60 * ((b - r) / difference) + 120, 360);
  } else {
    sensor_color->hue = fmod(60 * ((r - g) / difference) + 240, 360);
  }

  // caclulate saturation
  if (cmax == 0) {
    sensor_color->saturation = 0;
  } else {
    sensor_color->saturation = (difference / cmax) * 100;
  }

  // calculate value
  sensor_color->value = cmax * 100;

  return;
}

// Estimates the name for a color and gives an accuracy rating
//
void estimateColor(rgb_sensor_output *sensor_out) {
  calculateHSV(sensor_out);

  sensor_out->color = "Unknown";
  double min = MAX_HUE_DISTANCE;

  if (sensor_out->value < 20) {
    sensor_out->color = "Black";
    sensor_out->accuracy = 100 - sensor_out->value;
    return;
  } else if (sensor_out->value > 80) {
    sensor_out->color = "White";
    sensor_out->accuracy = sensor_out->value;
  }

  // Iterate through COLORS array comparing each rgb value to the sensor's
  // to find the color with the minimum distance
  for (unsigned int i = 0; i < sizeof(COLORS) / sizeof(Color); i++) {
    double distance = fabs(sensor_out->hue - COLORS[i].hue);
    if (distance < min) {
      min = distance;
      sensor_out->color = COLORS[i].colorname;
    }
  }

  sensor_out->accuracy = ((MAX_HUE_DISTANCE - min) / MAX_HUE_DISTANCE) * 100;

  return;
}

// Returns 0 on successfuly initialization
int initRGBSensor() {
  // Init GPIO connection
  if (DEV_RGB_ModuleInit() != 0) {
    return 1;
  }

  // Init the I2C connection
  if (TCS34725_Init() != 0) {
    printf("TCS34725 initialization error!!\r\n");
    return 1;
  }

  return 0;
}

void stopRGBSensor() {
  TCS34725_SetLight(0);
  DEV_RGB_ModuleExit();
}

// Populates a struct with information about the current sensor readings
// sensor_output is a pointer to a rgb_sensor_output struct to be populated
// fills out the rgb, R, G, B, color, and accuracy fields
void getRGBInfo(rgb_sensor_output *sensor_output) {
  RGB rgb = TCS34725_Get_RGBData();

  sensor_output->rgb = TCS34725_GetRGB888(rgb);

  // Bitwise calculation to isolate the R, G, and B
  sensor_output->R = sensor_output->rgb >> 16;
  sensor_output->G = (sensor_output->rgb >> 8) & 0xff;
  sensor_output->B = (sensor_output->rgb) & 0xff;

  // Fills out remaining color and accuracy fields
  estimateColor(sensor_output);
}

void *runColorSensor(void *arg) {
  (void)arg;
  initRGBSensor();

  rgb_sensor_output info;

  // RGB Test code
  // for (int i = 0; i < 20; i++) {
  //   getRGBInfo(&info);

  //   sleep(1);
  // }

  while (1) {
    getRGBInfo(&info);

    if (info.color[0] == 'R') {
      printf("Red detected\n");
      raise(SIG_STOP);
    }
  }

  stopRGBSensor();
}