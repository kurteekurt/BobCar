#ifndef INC_PIDMATH_H
#define INC_PIDMATH_H

int clamp(int value, int min, int max);
float fclamp(float value, float min, float max);
int inverseClamp(float value, float min, float max);

#endif // INC_PIDMATH_H