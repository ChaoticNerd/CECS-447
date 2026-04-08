// PWM.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Controls L and R PWM for car motors
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho

//////////////////////1. Pre-processor Directives Section////////////////////
#include "PWM.h"

////////// Local Global Variables //////////
/////////////////////////////////////////////////////////////////////////////
// PD01
//////////////////////3. Subroutines Section/////////////////////////////////
// Dependency: None
// Inputs: None
// Outputs: None
// Description: 
// Initializes the PWM module 0 generator 3 outputs A&B tied to PD0 and PD1 to be used with the 
//		L298N motor driver allowing for variable speed control of the robot car. 
void PWM1_PD01_Init(void) {
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	// Activate D clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)==0){};

    GPIO_PORTD_AFSEL_R |= 0x03;					// enable alt funct on PD0, PD1
	GPIO_PORTD_PCTL_R &= ~0x000000FF;   // clear PD0, PD1 PCTL
    GPIO_PORTD_PCTL_R |= 0x00000044;    // PD0=PWM0_6, PD1=PWM0_7
    GPIO_PORTD_DEN_R |= 0x03;           // enable digital I/O on PD0, PD1

    	// Initializes PWM settings	
	SYSCTL_RCGCPWM_R |= 0x01;           //  activate PWM0
	SYSCTL_RCC_R &= ~0x00100000;		// no PWM divider
	
    PWM0_3_CTL_R &= ~0x00000002;	// re-loading down-counting mode
	PWM0_3_GENA_R |= 0xC8;	        // low on LOAD, high on CMPA down
	PWM0_3_GENB_R |= 0xC08;	        // low on LOAD, high on CMPB down
	PWM0_3_LOAD_R = TOTAL_PERIOD - 1;	// cycles needed to count down to 0
    PWM0_3_CMPA_R = 0;	// count value when output rises
	PWM0_3_CMPB_R = 0;	// count value when output rises
	
	PWM0_3_CTL_R |= 0x00000001;	// Enable PWM0 Generator 3 in Countdown mode
	PWM0_ENABLE_R |= 0xC0; // enable PWM0 outputs 6 and 7
}


// Dependency: PWM_Init()
// Inputs: 
//	duty_L is the value corresponding to the duty cycle of the left wheel
//	duty_R is the value corresponding to the duty cycle of the right wheel
// Outputs: None 
// Description: Changes the duty cycles of PD0 and PD1 by changing the CMP registers
void PWM_Duty(unsigned long duty_L, unsigned long duty_R){
	PWM0_3_CMPA_R = duty_L - 1;	// PD0 (PWM0_6) count value when output rises
  	PWM0_3_CMPB_R = duty_R - 1;	// PD1 (PWM0_7) count value when output rises
}
/////////////////////////////////////////////////////////////////////////////
