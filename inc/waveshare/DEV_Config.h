#ifndef INC_DEV_CONFIG_H
#define INC_DEV_CONFIG_H

#include <stdint.h>

#include "sysfs_gpio.h"

#define DEV_SPI 0
#define DEV_I2C 1
#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t

extern uint32_t fd;
extern int INT_PIN;

uint8_t DEV_ModuleInit(void);
void DEV_ModuleExit(void);

void DEV_I2C_Init(uint8_t Add);
void I2C_Write_Byte(uint8_t Cmd, uint8_t value);
int I2C_Read_Byte(uint8_t Cmd);
int I2C_Read_Word(uint8_t Cmd);

void DEV_GPIO_Mode(UWORD Pin, UWORD Mode);
void DEV_Digital_Write(UWORD Pin, UBYTE Value);
UBYTE DEV_Digital_Read(UWORD Pin);

void DEV_Delay_ms(UDOUBLE xms);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);

#endif // !INC_DEV_CONFIG_H
