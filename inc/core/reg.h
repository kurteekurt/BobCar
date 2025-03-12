/**************************************************************
 * Class:: CSC-615-01 Spring 2024
 * Name:: Vignesh Guruswami
 * Student ID:: 922379195
 * Github-Name:: elitewhale75
 * Project:: CSC 615 Assignment Term Project
 *
 * File:: reg.h
 *
 * Description::
 * *************************************************************/

#ifndef REG_H
#define REG_H
#define BCM2710_PERI_BASE 0x3F000000
#define GPIO_BASE (BCM2710_PERI_BASE + 0x200000)

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4 * 1024)
#define BLOCK_SIZE (4 * 1024)
#define GPFSEL0 0x00               // Function Select 0
#define GPFSEL1 0x04               // Function Select 1
#define GPSET0 0x1C                // Pin Output Set 0
#define GPCLR0 0x28                // Pin Output Clear 0
#define GPIO_PULL *(gpio + 37)     // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio + 38) // Pull up/pull down clock

// I/O access
extern volatile unsigned *gpio;

/*
 * @brief Set up peripherals and memory map gpio
 */
void setupIo();
/*
 * @brief read high/low from GPIO pin
 * @param pin GPIO pin number
 *
 * @return HIGH/LOW reading from pin
 */
int gpioRead(int pin);
/*
 * @brief clear direction register bit for pin
 * @param pin GPIO pin number
 */
void gpioClear(int pin);
/*
 * @brief Set direction register bit to 1 for pin
 * @param pin GPIO pin number
 */
void gpioSet(int pin);
/*
 * @brief Set Pin Output to HIGH
 * @param pin GPIO pin number
 */
void setGpioInput(int pin);
/*
 * @brief Set pin output ot LOW
 * @param pin GPIO pin number
 */
void setGpioOutput(int pin);

#endif // !REG_H
