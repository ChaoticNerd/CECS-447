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
#include "UART5.h"
#include "../modules/ring_buffer.h"
extern int UART_ReadChar(RingBuffer *rb);
/*
 * Module initialization
 */
void UART5_Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5; // activate UART5
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // activate port B
    while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOE) == 0){}; 
		
    UART5_CTL_R = UART5_RESET;                     // reset UART5
    UART5_IBRD_R = IBRD_UART5;                    // IBRD = int(16,000,000 / (16 * 80,000)) = int(12.5)
    UART5_FBRD_R = FBRD_UART5;                     // FBRD = int(0.5 * 64 + 0.5) = 44
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
    UART5_LCRH_R = UART_LCRH_WLEN_8;
    UART5_IM_R |= UART_IM_RXIM;         // Enable RX interrupt

    UART5_CTL_R |= UART_CTL_UARTEN|UART_CTL_RXE|UART_CTL_TXE; // enable UART, Rx, Tx

    // PRI15 from P.152
    // Bits 15-13 from P.152**
    NVIC_PRI15_R = (NVIC_PRI15_R&PRI_CLEAR_UART5)|PRI_CLEAR_UART5; // bits 15-13, priority 5
    // IRQ = 61 from P.106 
    NVIC_EN1_R = NVIC_EN1_UART5;           // enable interrupt 5 in NVIC
    
        
    GPIO_PORTE_AFSEL_R |= UART5_MASK;           // enable alt funct on PE5-4
    GPIO_PORTE_DEN_R |= UART5_MASK;             // enable digital I/O on PE5-4
                                        // configure PE5-4 as UART
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&PCTL_CLEAR_UART5)|PCTL_SET_UART5;
    GPIO_PORTE_AMSEL_R &= ~UART5_MASK;          // disable analog functionality on PE5-4}
}

void UART5_OutChar(uint8_t data){
  while((UART5_FR_R&UART_FR_TXFF) != TXFF_FALSE);
  UART5_DR_R = data;
}

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none

void UART5_OutCRLF(void){
  UART5_OutChar(CR);
  UART5_OutChar(LF);
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART5_OutBuffer(RingBuffer *rb){
  char tempVar = UART_ReadChar(rb);
    while(tempVar != -1){
      UART5_OutChar(tempVar);
      tempVar = UART_ReadChar(rb);
    }
    UART5_OutChar(tempVar);
    UART5_OutChar('\0');
}



/*
SO BASICALLY (continuation from slides):
IRQ | Equation to find PRI-BITS
48      4n          
49      4n+1
50      4n+2
51      4n+3
52      4n
53      4n+1
54      4n+2
55      4n+3
56      4n
57      4n+1
58      4n+2
59      4n+3
60      4n
61      4n+1
62      4n+2
63      4n+3
It's the correct PRI BITs if the equation ends up as a whole.
n = IRQ
*/