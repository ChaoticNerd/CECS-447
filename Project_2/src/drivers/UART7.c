// UART7.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Communication from MCU_1 to MCU_2. To be used for MCU_2; Natasha Kho
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "UART7.h"
#include "../modules/ring_buffer.h"
extern int UART_ReadChar(RingBuffer *rb);

/*
 * Module initialization
 */
void UART7_Init(void){
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7; // activate UART7
		while((SYSCTL_RCGCUART_R&SYSCTL_RCGCUART_R7) == 0){};
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // activate port E
    while((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOE) == 0){}; 
		
    UART7_CTL_R = UART7_RESET;                     // reset UART7
    UART7_IBRD_R = FBRD_UART7;                    // IBRD = int(16,000,000 / (16 * 80,000)) = int(12.5)
    UART7_FBRD_R = FBRD_UART7;                     // FBRD = int(0.5 * 64 + 0.5) = 44
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
    UART7_LCRH_R = UART_LCRH_WLEN_8;
    UART7_IM_R |= UART_IM_RXIM;         // Enable RX interrupt

    UART7_CTL_R |= UART_CTL_UARTEN|UART_CTL_RXE|UART_CTL_TXE; // enable UART, Rx, Tx

    // PRI15 from P.152
    // Bits 31-29 from P.152**
    NVIC_PRI15_R = (NVIC_PRI15_R&PRI_CLEAR_UART7)|PRI_SET_UART7; // bits 31-29, priority 2
    // IRQ = 63 from P.106 
    NVIC_EN1_R = NVIC_EN1_UART7;           // enable interrupt 5 in NVIC
    
        
    GPIO_PORTE_AFSEL_R |= UART7_MASK;           // enable alt funct on PE1-0
    GPIO_PORTE_DEN_R |= UART7_MASK;             // enable digital I/O on PE1-0
                                        // configure PE1-0 as UART
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&PCTL_CLEAR_UART7)+PCTL_SET_UART7;
    GPIO_PORTE_AMSEL_R &= ~UART7_MASK;          // disable analog functionality on PE1-0}
}

//------------UART_OutBuffer------------
// Output String (NULL termination)
// Input: pointer to ring buffer that we want to output
// Output: none
void UART7_OutBuffer(RingBuffer *rb){
  char tempVar = UART_ReadChar(rb);
    while(tempVar != INVALID){
      UART7_OutChar(tempVar);
      tempVar = UART_ReadChar(rb);
    }
    UART7_OutChar(tempVar);
    UART7_OutChar('\0');
}


void UART7_OutChar(uint8_t data){
  while((UART7_FR_R&UART_FR_TXFF) != TXFF_FALSE);
  UART7_DR_R = data;
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