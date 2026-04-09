// car_drivers.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Enables GPIO Pins C67 and D67 (6 - dir, 7 SLP)
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho
#include "car_drivers.h"

void car_control_Init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	// Activate D clocks
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;	// Activate C clocks
    while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOC)==0){};
    while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)==0){};

    // SETTING UP PORT D 67
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTD_CR_R |= PORT67_PINS;         		// allow changes to PD67  
    GPIO_PORTD_AMSEL_R &= ~PORT67_PINS;     		// disable analog function
    GPIO_PORTD_PCTL_R &= ~PORT67_BITS; 	// GPIO clear bit PCTL  
    GPIO_PORTD_DIR_R |= PORT67_PINS;       		// PD67 input   
    GPIO_PORTD_AFSEL_R &= ~PORT67_PINS;     		// no alternate function
    GPIO_PORTD_DEN_R |= PORT67_PINS;        		// enable digital pins PD67

    // SETTING UP PORT C 67
		GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTC_CR_R |= PORT67_PINS;         		// allow changes to PC67    
    GPIO_PORTC_AMSEL_R &= ~PORT67_PINS;     		// disable analog function
    GPIO_PORTC_PCTL_R &= ~PORT67_BITS; 	// GPIO clear bit PCTL  
    GPIO_PORTC_DIR_R |= PORT67_PINS;       		// PC67 input   
    GPIO_PORTC_AFSEL_R &= ~PORT67_PINS;     		// no alternate function
    GPIO_PORTC_DEN_R |= PORT67_PINS;        		// enable digital pins PC67
}