// PWM.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Pulse Swift Modulation drivers and HAL to control LED - Hanna Estrada
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "../tm4c123gh6pm.h"
#include "../drivers/PWM.h"

// use PD0, PWM M1 PWM0
// PWM1_PF123_Init

void PWM1_PF123_Init(void) {

	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
	GPIO_PORTF_LOCK_R = PORTF_UNLOCK;   	// unlock PortF PF0  
	GPIO_PORTF_CR_R |= PORTF_RECONFIG;         		// allow changes to PF4-0 :11111->0x1F     
		
	GPIO_PORTF_AFSEL_R |= PORTF_MASK;        // no alternate function
  	GPIO_PORTF_PCTL_R &= ~PORTF_PCTL_CLEAR; 	// GPIO clear bit PCTL  
	GPIO_PORTF_PCTL_R |= PORTF_PCTL_SET;     

	GPIO_PORTF_DEN_R |= PORTF_MASK;          	// enable digital pins PF2    
		
	SYSCTL_RCGCPWM_R |= PWM_ACTIVATION;           //  activate PWM1
	SYSCTL_RCC_R &= ~PWM_DIVIDER;		// no PWM divider

	// generator 2
	PWM1_2_CTL_R &= ~PWM_CTL;	// re-loading down-counting mode
	//PWM1_2_GENA_R |= 0xC8;	        // low on LOAD, high on CMPA down
	PWM1_2_GENB_R |= PWM_GENB;	        // low on LOAD, high on CMPA down
	PWM1_2_LOAD_R = TOTAL_PERIOD;	// cycles needed to count down to 0
  	PWM1_2_CMPA_R = PWM_CMP_ZERO;	// count value when output rises
	PWM1_2_CMPB_R = PWM_CMP_ZERO;	// count value when output rises
		
	PWM1_3_CTL_R &= ~PWM_CTL;	// re-loading down-counting mode
	PWM1_3_GENA_R |= PWM_GENA;	        // low on LOAD, high on CMPA down
	PWM1_3_GENB_R |= PWM_GENB;	        // low on LOAD, high on CMPA down
	PWM1_3_LOAD_R = TOTAL_PERIOD;	// cycles needed to count down to 0
	PWM1_3_CMPA_R = PWM_CMP_ZERO;	// count value when output rises
	PWM1_3_CMPB_R = PWM_CMP_ZERO;	// count value when output rises
	
	
	PWM1_2_CTL_R |= PWM1_COUNTDOWN_CTL;	// Enable PWM0 Generator 0 in Countdown mode
	PWM1_3_CTL_R |= PWM1_COUNTDOWN_CTL;	// Enable PWM0 Generator 0 in Countdown mode
	PWM1_ENABLE_R |= PWM1_ENABLE;	// Enable PB54:PWM0 output 0&1 on initialization*

}


void ActivateLED(char LED_color, unsigned long brightness_duty) {
	switch(LED_color){
        case 114:
			PWM1_2_CMPB_R = brightness_duty - 1;
			PWM1_3_CMPA_R = PWM_CMP_ZERO;
			PWM1_3_CMPB_R = PWM_CMP_ZERO;
            break;
        case 98:
        	PWM1_2_CMPB_R = PWM_CMP_ZERO;
			PWM1_3_CMPA_R = brightness_duty - 1;
			PWM1_3_CMPB_R = PWM_CMP_ZERO;
            break;
        case 103:
        	PWM1_2_CMPB_R = PWM_CMP_ZERO;
			PWM1_3_CMPA_R = PWM_CMP_ZERO;
			PWM1_3_CMPB_R = brightness_duty - 1;
            break;
        case 121:
        	PWM1_2_CMPB_R = brightness_duty - 1;
			PWM1_3_CMPA_R = PWM_CMP_ZERO;
			PWM1_3_CMPB_R = brightness_duty - 1;
            break;
        case 99:
        	PWM1_2_CMPB_R = PWM_CMP_ZERO;
			PWM1_3_CMPA_R = brightness_duty - 1;
			PWM1_3_CMPB_R = brightness_duty - 1;
            break;
        case 112:
        	PWM1_2_CMPB_R = brightness_duty - 1;
			PWM1_3_CMPA_R = brightness_duty - 1;
			PWM1_3_CMPB_R = PWM_CMP_ZERO;
            break;
        case 119:
        	PWM1_2_CMPB_R = brightness_duty - 1;
			PWM1_3_CMPA_R = brightness_duty - 1;
			PWM1_3_CMPB_R = brightness_duty - 1;
            break;
        case 100:
        	PWM1_2_CMPB_R = PWM_CMP_ZERO;
			PWM1_3_CMPA_R = PWM_CMP_ZERO;
			PWM1_3_CMPB_R = PWM_CMP_ZERO;
            break;
    }

}
