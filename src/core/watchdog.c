#include "core/watchdog.h"
#include "drivers/linefollow_PID_SLR.h"
#include "drivers/motor_driver.h"
#include "sensors/line_sensors.h"
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t state_lock = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t *line_follower_lock;
static ControlValues *ctrl_values;

void handleObstacle() {
  pthread_mutex_lock(&state_lock);
  pthread_mutex_lock(line_follower_lock);
  // TODO: activate obstacle avoidance, disable obstacle detection
  int speed = 50;
  struct timespec three_quarter_second = {0, 75000000};
  struct timespec quarter_second = {0, 25000000};
  struct timespec half_second = {0, 500000000};
  struct timespec one_and_half_second = {1, 500000000};
  struct timespec one_second = {1, 0};
  printf("Obstacle hit\n");
  motorMove(RIGHT_MOTOR, 0);
  motorMove(LEFT_MOTOR, 0);
  nanosleep(&half_second, NULL);
  // reverse
  motorMove(RIGHT_MOTOR, -speed);
  motorMove(LEFT_MOTOR, -speed);
  nanosleep(&half_second, NULL);
  // left turn
  motorMove(LEFT_MOTOR, speed);
  motorMove(RIGHT_MOTOR, 0);
  nanosleep(&half_second, NULL);
  // drive straight
  motorMove(RIGHT_MOTOR, speed);
  motorMove(LEFT_MOTOR, speed);
  nanosleep(&half_second, NULL);
  // right turn
  motorMove(LEFT_MOTOR, 0);
  motorMove(RIGHT_MOTOR, speed);
  nanosleep(&half_second, NULL);
  // drive straight
  motorMove(RIGHT_MOTOR, speed);
  motorMove(LEFT_MOTOR, speed);
  nanosleep(&half_second, NULL);
  while (sensor_array[4] == 0 && sensor_array[5] == 0 && sensor_array[6] == 0) {
  };
  pthread_mutex_unlock(line_follower_lock);
  pthread_mutex_unlock(&state_lock);
}

void handleLineFollow() {
  pthread_mutex_lock(&state_lock);
  pthread_mutex_unlock(line_follower_lock);
  // TODO: disable obstacle avoidance, enable obstacle detection
  pthread_mutex_unlock(&state_lock);
}

void handleSlow() {
  pthread_mutex_lock(&state_lock);
  pthread_mutex_lock(line_follower_lock);
  // TODO: disable obstacle detection
  motorMove(RIGHT_MOTOR, ctrl_values->lfSpeed / 2);
  motorMove(LEFT_MOTOR, ctrl_values->lfSpeed / 2);
  pthread_mutex_unlock(&state_lock);
}

void handleStop() {
  printf("Stop\n");
  pthread_mutex_lock(&state_lock);
  pthread_mutex_lock(line_follower_lock);
  // TODO: disable obstacle detection and avoidance
  motorStop();
  pthread_mutex_unlock(&state_lock);
}

void *runWatchdog(void *arg) {
  WatchdogArgs *watchdog_args = (WatchdogArgs *)arg;
  line_follower_lock = watchdog_args->line_follower_lock;
  ctrl_values = watchdog_args->ctr_values;

  signal(SIG_OBSTACLE, handleObstacle);
  signal(SIG_LINEFOLLOW, handleLineFollow);
  signal(SIG_SLOW, handleSlow);
  signal(SIG_STOP, handleStop);

  //   while (1) {
  //     pthread_mutex_lock(&state_lock);
  //     if (current_state == OBSTACLE_AVOIDANCE) {
  //     } else if (current_state == LINE_FOLLOWING) {
  //     }
  //     pthread_mutex_unlock(&state_lock);
  //     sleep(1);
  //   }
  return NULL;
}