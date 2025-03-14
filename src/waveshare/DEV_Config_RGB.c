/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2019-01-18
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "waveshare/DEV_Config_RGB.h"

int fd;

/******************************************************************************
function:   Set the I2C device address
parameter	:
        Add : Device address
******************************************************************************/
void DEV_Set_I2CAddress(UBYTE Add) { fd = wiringPiI2CSetup(Add); }
/******************************************************************************
function:
        I2C Write and Read
******************************************************************************/
void DEV_I2C_WriteByte(UBYTE add_, UBYTE data_) {
  wiringPiI2CWriteReg8(fd, add_, data_);
}

void DEV_I2C_WriteWord(UBYTE add_, UWORD data_) {
  wiringPiI2CWriteReg16(fd, add_, data_);
}

UBYTE DEV_I2C_ReadByte(UBYTE add_) { return wiringPiI2CReadReg8(fd, add_); }

UWORD DEV_I2C_ReadWord(UBYTE add_) { return wiringPiI2CReadReg16(fd, add_); }
/******************************************************************************
function:
        Module exits
******************************************************************************/
void DEV_RGB_ModuleExit(void) {}

/******************************************************************************
function:
        Module initialization, BCM2835 library and initialization pins,
        I2C protocol
******************************************************************************/
UBYTE DEV_RGB_ModuleInit(void) {
  // if (wiringPiSetupGpio() < 0) { // use BCM2835 Pin number table
  //   printf("set wiringPi lib failed	!!! \r\n");
  //   return 1;
  // } else {
  //   printf("set wiringPi lib success  !!! \r\n");
  // }

  // I2C Config
  fd = wiringPiI2CSetup(IIC_Addr);

  // PWM Config
  softPwmCreate(PWM_PIN, 10, 100);

  pinMode(INT_PIN, INPUT);
  pullUpDnControl(INT_PIN, PUD_UP);
  return 0;
}

/************************************************/
