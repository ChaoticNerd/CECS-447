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
// Initializes the PWM module 0 generator 1 outputs A&B tied to PB54 to be used with the 
//		L298N motor driver allowing for a variable speed of robot car. 
void PWM1_PD01_Init(void) {
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	// Activate D clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)==0){};

    GPIO_PORTD_AFSEL_R |= PORT01_PINS;					// enable alt funct on PD0
	GPIO_PORTD_PCTL_R &= ~PORT01_CLEAR_PCTL;   // clear PD0 PTCL
    GPIO_PORTD_PCTL_R |= PORT01_SET_PCTL;    // set PD0 to PWM1_0
    GPIO_PORTD_DEN_R |= PORT01_PINS;           // enable digital I/O on PB5,4

    	// Initializes PWM settings	
	SYSCTL_RCGCPWM_R |= SYSCTL_RCC_NO_DIV;           //  activate PWM1
	SYSCTL_RCC_R &= ~SYSCTL_RCGCPWM0;		// no PWM divider
	
    PWM0_3_CTL_R &= ~PWM0_3_CTL;	// re-loading down-counting mode
	PWM0_3_GENA_R |= PWM0_3_GENA;	        // low on LOAD, high on CMPA down
	PWM0_3_GENB_R |= PWM0_3_GENB;	        // low on LOAD, high on CMPA down
	PWM0_3_LOAD_R = TOTAL_PERIOD - 1;	// cycles needed to count down to 0
    PWM0_3_CMPA_R = 0;	// count value when output rises
	PWM0_3_CMPB_R = 0;	// count value when output rises
	
	PWM0_3_CTL_R |= EN_PWM0_3;	// Enable PWM0 Generator 0 in Countdown mode
}

// Dependency: PWM_Init()
// Inputs: 
//	duty_L is the value corresponding to the duty cycle of the left wheel
//	duty_R is the value corresponding to the duty cycle of the right wheel
// Outputs: None 
// Description: Changes the duty cycles of PB76 by changing the CMP registers
void PWM_Duty(unsigned long duty_L, unsigned long duty_R){
	PWM0_3_CMPA_R = duty_L - 1;	// PB4 count value when output rises
  	PWM0_3_CMPB_R = duty_R - 1;	// PB5 count value when output rises
}
/////////////////////////////////////////////////////////////////////////////
