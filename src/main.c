#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#include "camera/opencvProcessing.h"
#include "core/tests.h"
#include "core/watchdog.h"
#include "drivers/linefollow_PID_SLR.h"
#include "drivers/motor_driver.h"
#include "sensors/ir_sensor.h"
#include "sensors/line_sensors.h"
#include "sensors/rgb_sensor.h"

#define BUTTON_PIN 6

pthread_t line_follower_thread;
pthread_t line_sense_thread;
pthread_t ir_thread;
pthread_t color_sensor_thread;
pthread_t watchdog_thread;

pthread_t testing_thread;

void handler() {
  // pthread_cancel(line_follower_thread);
  pthread_cancel(line_sense_thread);
  motorStop();
  exit(0);
}

void buttonWait(void) {
  pinMode(BUTTON_PIN, INPUT);
  pullUpDnControl(BUTTON_PIN, PUD_DOWN);

  while (digitalRead(BUTTON_PIN) == 0) {
  }

  sleep(1);
}

int main() {
  ControlValues *ctrl_values;
  pthread_mutex_t *line_follower_lock;
  pthread_mutex_t *ir_lock;

  signal(SIGINT, handler);

  if (wiringPiSetupGpio() < 0) {
    printf(" wiringPiInitialize failed\n");
    exit(EXIT_FAILURE);
  }

  // Initialize this struct
  ctrl_values = malloc(sizeof(*ctrl_values));
  if (ctrl_values == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  ctrl_values->gain_p = 7;
  ctrl_values->gain_i = 0.01;
  ctrl_values->gain_d = 48;
  ctrl_values->lfSpeed = 50;

  line_follower_lock = malloc(sizeof(pthread_mutex_t));
  if (line_follower_lock == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  *line_follower_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

  ir_lock = malloc(sizeof(pthread_mutex_t));
  if (ir_lock == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  *ir_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

  LinefollowPIDArg *pid_arg = malloc(sizeof(LinefollowPIDArg));
  if (pid_arg == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  *pid_arg = (LinefollowPIDArg){ctrl_values, line_follower_lock};

  WatchdogArgs *watchdog_args = malloc(sizeof(WatchdogArgs));
  if (watchdog_args == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  *watchdog_args = (WatchdogArgs){ctrl_values, line_follower_lock};

  initializeLineSensors();

  // buttonWait();

  pthread_create(&line_sense_thread, NULL, lineSensorRead, NULL);
  pthread_create(&ir_thread, NULL, runIRSensor, ir_lock);
  pthread_create(&line_follower_thread, NULL, initializePID, pid_arg);
  pthread_create(&color_sensor_thread, NULL, runColorSensor, NULL);
  pthread_create(&watchdog_thread, NULL, runWatchdog, watchdog_args);
  // pthread_create(&testing_thread, NULL, runTests, NULL);

  // pthread_join(testing_thread, NULL);
  pthread_join(watchdog_thread, NULL);
  pthread_join(color_sensor_thread, NULL);
  pthread_join(line_follower_thread, NULL);
  pthread_join(ir_thread, NULL);
  pthread_join(line_sense_thread, NULL);

  motorStop();

  free(line_follower_lock);
  free(ir_lock);
  free(watchdog_args);
  free(ctrl_values); // Free the allocated memory
  free(pid_arg);
  free((void *)sensor_array);

  return 0;
}