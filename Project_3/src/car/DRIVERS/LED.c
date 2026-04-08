// LED.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Controls on-board LEDs
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho

#include "LED.h"

// ~~~~~~~~~~     LED_Init     ~~~~~~~~~~
// Used to initialize onboard LEDS. Only used for testing
// Input: none
// Output: none
void LED_Init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
		
    GPIO_PORTF_AMSEL_R &= ~0x0E;      // 3) disable analog function
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // 4) GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R |= 0x0E;         // 6) PF1-PF3 output
    GPIO_PORTF_AFSEL_R &= ~0x0E;      // 7) no alternate function     
    GPIO_PORTF_DEN_R |= 0x0E;         // 8) enable digital pins PF3-PF1
    LED = 0x00;                       // Turn off all LEDs.
}

// ~~~~~~~~~~     change_LED     ~~~~~~~~~~
// Used to change LED colors in FSM
// Input: uint8_t color
// Output: none
void change_LED(uint8_t color){
    LED = color;
}