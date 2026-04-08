// UART5.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Communication from MCU_2 to MCU_1. To be used for MCU_1; Justin Narciso
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

// IRQ 61
#define NVIC_EN1_UART5 (1<<29)
#define IBRD_UART5       12
#define FBRD_UART5       35
#define PRI_SET_UART5   0x00004000
#define PRI_CLEAR_UART5 0xFFFF1FFF
#define UART5_MASK  0x30
#define UART5_RESET 0
#define PCTL_SET_UART5   0x00110000
#define PCTL_CLEAR_UART5 0xFF00FFFF
#define INVALID -1
#define TXFF_FALSE 0


// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A

#define GAMMAL 0xE2 // MCU_2 "enter waiting" M3 
#define HELI 0xE9   // MCU_2 "transmission" M3 
#define ANGRY 0xCE  // TOXIC YURI MCU_2 LISTEN ONLY M1
#define FLAG 0xD5   // MCU_1 "I HAVE TALKING STICK" M3
#define KEBAB 0xED  // MCU_1 "I have kebab and no talk" M3
#define BETA 0xE1   // ENTERING M2 GET READY BESH
#define GRADEM 0xB1 // EXIT TO MAIN MENU M3 & M2 & M1

void UART5_Init(void);
void UART5_OutChar(uint8_t data);
void UART5_OutCRLF(void);

//------------UART_OutBuffer------------
// Output String (NULL termination)
// Input: pointer to ring buffer that we want to output
// Output: none
void UART5_OutBuffer(RingBuffer *rb);
