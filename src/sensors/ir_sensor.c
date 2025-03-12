#include "sensors/ir_sensor.h"
#include "core/watchdog.h"
#include <pthread.h>
#include <signal.h>
#include <wiringPi.h>

#define IR_PIN 19

void *runIRSensor(void *arg) {
  pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
  pinMode(IR_PIN, INPUT);

  while (1) {
    pthread_mutex_lock(mutex);
    if (digitalRead(IR_PIN) == 0) {
      raise(SIG_OBSTACLE);
    }
    pthread_mutex_unlock(mutex);
  }

  return NULL;
}