#include "core/tests.h"
#include "core/watchdog.h"

void testObjAvoid() {}

void *runTests(void *arg) {
  (void)arg;

  sleep(1);
  raise(SIG_OBSTACLE);
  // raise(SIG_STOP); // set up the STOP state
  // sleep(1);
  // raise(SIG_LINEFOLLOW);

  return (void *)0;
}