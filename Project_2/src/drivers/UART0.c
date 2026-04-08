// UART0.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: 
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada
#include "../tm4c123gh6pm.h"
#include "../drivers/UART0.h"
extern int UART_ReadChar(RingBuffer *rb);


void UART0_Init(void){
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0; // activate UART0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // activate port A
	
  UART0_CTL_R = UART0_RESET;                      // disable UART
	#ifdef MCU_1
  UART0_IBRD_R = IBRD_UART0_MCU1;                    // IBRD = int(16,000,000 / (16 * 460800)) = int(2.170138889) //MCU1/UART5 IBRD = 1, FBRD = 5; MCU2/UART7 IBRD = 2, FBRD = 11
  UART0_FBRD_R = FBRD_UART0_MCU1;                     // FBRD = int(.170138889 * 64 + 0.5) = 11
  #endif                                // 8 bit word length (no parity bits, one stop bit,  FIFOs enabled)
	#ifdef MCU_2
  UART0_IBRD_R = IBRD_UART0_MCU2;                    // IBRD = int(16,000,000 / (16 * 460800)) = int(2.170138889) //MCU1/UART5 IBRD = 1, FBRD = 5; MCU2/UART7 IBRD = 2, FBRD = 11
  UART0_FBRD_R = FBRD_UART0_MCU2;                     // FBRD = int(.170138889 * 64 + 0.5) = 11
  #endif            
  UART0_LCRH_R = UART_LCRH_WLEN_8|UART_LCRH_FEN; // For simulator FIFO has to be enabled.
	UART0_IFLS_R = UART0_IFLS;
	
  UART0_CTL_R |= UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN;// enable Tx, RX and UART
  UART0_IM_R |= UART_IM_RXIM;         // Enable RX interrupt
	
	  // PRI1 from P.152
    // Bits 15-13 from P.152**
    NVIC_PRI1_R = (NVIC_PRI1_R&PRI_CLEAR_UART0)|PRI_SET_UART0; // bits 15-13, priority 5
    // IRQ = 5 from P.106 
    NVIC_EN0_R = NVIC_EN1_UART0;           // enable interrupt 5 in NVIC
	
  GPIO_PORTA_AFSEL_R |= UART0_MASK;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= UART0_MASK;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&PCTL_CLEAR_UART0)+PCTL_SET_UART0;
  GPIO_PORTA_AMSEL_R &= ~UART0_MASK;          // disable analog functionality on PA
}

// cr: carriage return to beginning of line
// lf: move cursor down a line
void UART0_OutCRLF(void){
  UART0_OutChar(CR);
  UART0_OutChar(LF);
}

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART0_OutChar(uint8_t data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//------------UART_OutBUFFER------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART0_OutBuffer(RingBuffer *rb){
  char tempVar = UART_ReadChar(rb);
    while(tempVar != -1){
      UART0_OutChar(tempVar);
      tempVar = UART_ReadChar(rb);
    }
		UART0_OutCRLF();
    //UART0_OutChar(tempVar);
}

void UART0_OutString(char str[]){
	int i =  0;
  while(str[i] != '\0'){
    UART0_OutChar(str[i]);
		i++;
  }
}