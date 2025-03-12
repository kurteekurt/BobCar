#include "waveshare/PCA9685.h"
#include <math.h>

static void PCA9685_WriteByte(UBYTE reg, UBYTE value) {
  I2C_Write_Byte(reg, value);
}

static UBYTE PCA9685_ReadByte(UBYTE reg) { return I2C_Read_Byte(reg); }

static void PCA9685_SetPWM(UBYTE channel, UWORD on, UWORD off) {
  PCA9685_WriteByte(LED0_ON_L + 4 * channel, on & 0xFF);
  PCA9685_WriteByte(LED0_ON_H + 4 * channel, on >> 8);
  PCA9685_WriteByte(LED0_OFF_L + 4 * channel, off & 0xFF);
  PCA9685_WriteByte(LED0_OFF_H + 4 * channel, off >> 8);
}

void PCA9685_Init(char addr) {
  DEV_I2C_Init(addr);
  I2C_Write_Byte(MODE1, 0x00);
}

void PCA9685_SetPWMFreq(UWORD freq) {
  freq *=
      0.9; // Correct for overshoot in the frequency setting (see issue #11).
  double prescaleval = 25000000.0;
  prescaleval /= 4096.0;
  prescaleval /= freq;
  prescaleval -= 1;

  UBYTE prescale = floor(prescaleval + 0.5);

  UBYTE oldmode = PCA9685_ReadByte(MODE1);
  UBYTE newmode = (oldmode & 0x7F) | 0x10; // sleep

  PCA9685_WriteByte(MODE1, newmode);     // go to sleep
  PCA9685_WriteByte(PRESCALE, prescale); // set the prescaler
  PCA9685_WriteByte(MODE1, oldmode);
  DEV_Delay_ms(5);
  PCA9685_WriteByte(
      MODE1,
      oldmode |
          0x80); //  This sets the MODE1 register to turn on auto increment.
}

void PCA9685_SetPwmDutyCycle(UBYTE channel, UWORD pulse) {
  PCA9685_SetPWM(channel, 0, pulse * (4096 / 100) - 1);
}

void PCA9685_SetLevel(UBYTE channel, UWORD value) {
  if (value == 1)
    PCA9685_SetPWM(channel, 0, 4095);
  else
    PCA9685_SetPWM(channel, 0, 0);
}
