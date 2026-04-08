// UART7.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Communication from MCU_1 to MCU_2. To be used for MCU_2; Natasha Kho
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "../tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include "../modules/ring_buffer.h"
#include "../config.h"

#define NVIC_EN1_UART7   1<<31
#define IBRD_UART7       12
#define FBRD_UART7       35
#define PRI_SET_UART7   0x40000000
#define PRI_CLEAR_UART7 0x1FFFFFFF
#define UART7_MASK  0x03
#define UART7_RESET 0
#define PCTL_SET_UART7   0x00000011
#define PCTL_CLEAR_UART7 0xFFFFFF00
#define INVALID -1
#define TXFF_FALSE 0

void UART7_Init(void);
void UART7_Handler(void);
void UART7_OutChar(uint8_t data);
void UART7_OutBuffer(RingBuffer *rb);