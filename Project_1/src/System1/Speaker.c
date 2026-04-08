// Speaker.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "../tm4c123gh6pm.h"
#include "../System1/Speaker.h"

// ~~~~~~~~~~     Speaker_Init     ~~~~~~~~~~
// Used to initialize Speakers to Port E4. Sets E4 to output sound bytes to speaker.
// Input: none
// Output: none
void Speaker_Init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;		// set up PortE to be used
	while ((SYSCTL_RCGCGPIO_R&SYSCTL_RCGC2_GPIOE)!=SYSCTL_RCGC2_GPIOE){} // wait for Port E to be ready
		
		GPIO_PORTE_CR_R |= SPEAKER_IN;         			// allow changes to PE4
    GPIO_PORTE_AMSEL_R &= ~SPEAKER_IN;     			// disable analog function for PE4
    GPIO_PORTE_PCTL_R &= ~SPEAKER_CLEAR_PCTL; 	// set PE4 to GPIO function
    GPIO_PORTE_DIR_R |= SPEAKER_IN;       			// set PE4 to output pin
    GPIO_PORTE_AFSEL_R &= ~SPEAKER_IN;     			// clear PE4 for no alternate function
    GPIO_PORTE_DEN_R |= SPEAKER_IN;        			// set PE4 to enable digital pins
}