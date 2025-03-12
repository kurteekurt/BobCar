#ifndef INC_WATCHDOG_H
#define INC_WATCHDOG_H

#include "drivers/linefollow_PID_SLR.h"
#include <pthread.h>
#include <signal.h>

#define SIG_OBSTACLE SIGUSR1
#define SIG_LINEFOLLOW SIGUSR2
#define SIG_SLOW SIGRTMAX
#define SIG_STOP SIGRTMIN

typedef struct {
  ControlValues *ctr_values;
  pthread_mutex_t *line_follower_lock;
} WatchdogArgs;

void *runWatchdog(void *control_arg);

#endif