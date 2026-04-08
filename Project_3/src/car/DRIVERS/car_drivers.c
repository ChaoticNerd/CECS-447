// initialize PD67 - right side - dir/slp 
// initialize PC67 - left side - dir/slp
#include "car_drivers.h"

void car_control_Init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	// Activate D clocks
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;	// Activate C clocks
    while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOC)==0){};
    while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)==0){};

    // SETTING UP PORT D 67
		GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTD_CR_R |= 0xC0;         		// allow changes to PD67  
    GPIO_PORTD_AMSEL_R &= ~0xC0;     		// disable analog function
    GPIO_PORTD_PCTL_R &= ~0xFF000000; 	// GPIO clear bit PCTL  
    GPIO_PORTD_DIR_R |= 0xC0;        	// PD67 output   
    GPIO_PORTD_AFSEL_R &= ~0xC0;      	// no alternate function
    GPIO_PORTD_DEN_R |= 0xC0;        		// enable digital pins PD67

    // SETTING UP PORT C 67
		GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTC_CR_R |= 0xC0;         		// allow changes to PC67    
    GPIO_PORTC_AMSEL_R &= ~0xC0;     		// disable analog function
    GPIO_PORTC_PCTL_R &= ~0xFF000000; 	// GPIO clear bit PCTL  
    GPIO_PORTC_DIR_R |= 0xC0;        		// PC67 output   
    GPIO_PORTC_AFSEL_R &= ~0xC0;     		// no alternate function
    GPIO_PORTC_DATA_R &= ~0xC0;       		// default sleep/direction low
    GPIO_PORTC_DEN_R |= 0xC0;        		// enable digital pins PC67
}
