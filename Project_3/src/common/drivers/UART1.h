// UART1.h
// Runs on TM4C123 or LM4F120
// this connection occurs in the USB debugging cable
// U1Rx (PB0)
// U1Tx (PB1)
// Ground connected ground in the USB cable
// By Hanna Estrada

#include <stdint.h>
#include "../../tm4c123gh6pm.h"


#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define SP   0x20


//------------UART1_Init------------
// Initialize the UART1 for 115200 baud rate (assuming 80 MHz clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART1_Init(void);

//------------UART1_OutChar------------
// Output 8-bit to serial port UART1
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART1_OutChar(uint8_t data);

//------------UART1_OutString------------
// Output String (NULL termination) to UART1
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART1_OutString(uint8_t *pt);

//------------UART1_InChar------------
// Wait for new serial port input from UART1
// Input: none
// Output: ASCII code for key typed
uint8_t UART1_InChar(void);

//------------UART1_InString------------
// Gets reply from HC-05 Bluetooth module through UART1
void UART1_InString(uint8_t *bufPt);
