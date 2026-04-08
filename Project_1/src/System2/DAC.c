// DAC.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "DAC.h"


// ~~~~~~~~~~     DAC_Init     ~~~~~~~~~~
// Used to initialize 6-bit DAC to receive signals from microcontroller.
// DAC bit 0 on PD0 (least significant bit)
// DAC bit 1 on PD1
// DAC bit 2 on PD2
// DAC bit 3 on PD3
// DAC bit 4 on PD6
// DAC bit 5 on PD7 (most significant bit)
// Input: none
// Output: none
void DAC_Init(void) {
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate Port D
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)!=SYSCTL_RCGC2_GPIOD){} // wait for Port D to set up
		
	GPIO_PORTD_LOCK_R =  0x4C4F434B;
		GPIO_PORTD_DR8R_R |= DAC_Pins;
	GPIO_PORTD_AMSEL_R &= ~DAC_Pins;  // clear AMSEL for only digital function
	GPIO_PORTD_AFSEL_R &= ~DAC_Pins;  // clear AFSEL to disable alternate function
  GPIO_PORTD_PCTL_R &= ~DAC_PCTL; // clear PCTL to set regular function
  GPIO_PORTD_DIR_R |= DAC_Pins;     // set all Port D pins to output
  GPIO_PORTD_DEN_R |= DAC_Pins;     // set all Port D pins to use digital I/O	
}


// ~~~~~~~~~~     DAC_Out     ~~~~~~~~~~
// Outputs digital signals to DAC.
// Input: 6-bit data, which is converted to analog signal via (data * 3.3V) / (2^6 - 1)
// Output: none
void DAC_Out(uint8_t data){
  DAC = data;
}


