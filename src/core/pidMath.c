#include "core/pidMath.h"
int clamp(int value, int min, int max) {
  if (value > max) {
    return max;
  } else if (value < min) {
    return min;
  } else {
    return value;
  }
}

float fclamp(float value, float min, float max) {
  if (value > max) {
    return max;
  } else if (value < min) {
    return min;
  } else {
    return value;
  }
}

int inverseClamp(float value, float min, float max) {
  if (value > min && value < max) {
    return value;
  }
  return 0;
}