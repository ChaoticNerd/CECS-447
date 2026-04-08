// UART0.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: 
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

#include <stdint.h>
#include "../modules/ring_buffer.h"
#include "../config.h"

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F
#define NULL 0
#define NVIC_EN1_UART0   1<<5
#define IBRD_UART0_MCU1   1
#define FBRD_UART0_MCU1  5
#define IBRD_UART0_MCU2   2
#define FBRD_UART0_MCU2   11
#define PRI_SET_UART0   0x00008000
#define PRI_CLEAR_UART0 0xFFFF1FFF
#define UART0_MASK  0x03
#define UART0_RESET 0
#define PCTL_SET_UART0   0x00000011
#define PCTL_CLEAR_UART0 0xFFFFFF00
#define INVALID -1
#define TXFF_FALSE 0
#define UART0_IFLS 0x00


//------------UART_Init------------
// Initialize the UART for 115,200 baud rate (assuming 50 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART0_Init(void);

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void UART0_OutCRLF(void);

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
uint8_t UART0_InChar(void);

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(uint8_t data);

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutString(char str[]);

//------------UART_OutBuffer------------
// Output String (NULL termination)
// Input: pointer to ring buffer that we want to output
// Output: none
void UART0_OutBuffer(RingBuffer *rb);

