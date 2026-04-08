// Switches.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles SW1 and SW2 onboard buttons; Justin Narciso, Natasha Kho
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "Switches.h"

bool SW1_pressed = false;
bool SW2_pressed = false;

// ~~~~~~~~~~     Board_BTNS_init     ~~~~~~~~~~
// Used to initialize onboard Buttons with interrupt. Use SW1 to exit Mode 3 or send color to
// receiving MCU, use SW2 to change LED color on transmitting MCU.
// Input: none
// Output: none
void Board_BTNS_Init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
    GPIO_PORTF_LOCK_R = UNLOCK_PORTF0;           // UNLOCK PF0

    GPIO_PORTF_CR_R |= BOARD_BTNS_IN;         		// allow changes to PF0,4     
    GPIO_PORTF_AMSEL_R &= ~BOARD_BTNS_IN;     		// disable analog function
    GPIO_PORTF_PCTL_R &= ~BOARD_BTNS_CLEAR_PCTL; 	// GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R &= ~BOARD_BTNS_IN;       		// PF4,0 input   
    GPIO_PORTF_AFSEL_R &= ~BOARD_BTNS_IN;     		// no alternate function
    GPIO_PORTF_PUR_R |= BOARD_BTNS_PUR;          	// enable pullup resistors on PF4,0       
    GPIO_PORTF_DEN_R |= BOARD_BTNS_IN;        		// enable digital pins PF4,0

    GPIO_PORTF_IS_R &= ~(SW1_MASK|SW2_MASK);    	// PF4,0 is edge-sensitive
    GPIO_PORTF_IBE_R &= ~(SW1_MASK|SW2_MASK);   	// PF4,0 is not both edges
    GPIO_PORTF_IEV_R |= (SW1_MASK|SW2_MASK);    	// PF4,0 rising edge event 
    GPIO_PORTF_ICR_R |= (SW1_MASK|SW2_MASK);    	// Clear Flag4,0
    GPIO_PORTF_IM_R |= (SW1_MASK|SW2_MASK);     	// Arm interrupt on PF4,0
    
		NVIC_EN0_R = NVIC_EN0_BTNS;
}


// ~~~~~~~~~~     GPIOPortF_Handler     ~~~~~~~~~~
// Used to acknowledge SW1 and SW2 interrupts. Both SW1 and SW2 invert SW1/2_Pressed flags.
// Input: none
// Output: none
void GPIOPortF_Handler(void){
    // simple solution to take care of button debounce: 20ms to 30ms delay
    for (uint32_t i=0;i<160000;i++) {}

    // if F0 was pressed, set SW1_pressed variable to true
    if( GPIO_PORTF_RIS_R&SW1_MASK){
        SW1_pressed = true;
        GPIO_PORTF_ICR_R |= SW1_MASK;
    } 

    // if F4 was pressed, invert mode (switch between piano and autoplay)
    if( GPIO_PORTF_RIS_R&SW2_MASK){
        SW2_pressed = true;
        GPIO_PORTF_ICR_R |= SW2_MASK;
    }
}