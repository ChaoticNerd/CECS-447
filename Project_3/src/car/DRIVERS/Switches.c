// Switches.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: Handles SW1 and SW2 onboard buttons
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
// main contributor: Natasha Kho

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "Switches.h"

bool SW1_PRESSED = false;

// ~~~~~~~~~~     Board_BTNS_init     ~~~~~~~~~~
// Used to initialize onboard Buttons with interrupt. Use SW1 to exit Mode 3 or send color to
// receiving MCU, use SW2 to change LED color on transmitting MCU.
// Input: none
// Output: none
void Switch_Init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
    GPIO_PORTF_LOCK_R = UNLOCK_PORTF0;           // UNLOCK PF0

    GPIO_PORTF_CR_R |= BOARD_BTNS_IN;         		// allow changes to PF4     
    GPIO_PORTF_AMSEL_R &= ~BOARD_BTNS_IN;     		// disable analog function
    GPIO_PORTF_PCTL_R &= ~BOARD_BTNS_CLEAR_PCTL; 	// GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R &= ~BOARD_BTNS_IN;       		// PF4 input   
    GPIO_PORTF_AFSEL_R &= ~BOARD_BTNS_IN;     		// no alternate function
    GPIO_PORTF_PUR_R |= BOARD_BTNS_IN;          	// enable pullup resistors on PF4       
    GPIO_PORTF_DEN_R |= BOARD_BTNS_IN;        		// enable digital pins PF4

    GPIO_PORTF_IS_R &= ~(SW1_MASK);    	// PF4 is edge-sensitive
    GPIO_PORTF_IBE_R &= ~(SW1_MASK);   	// PF4 is not both edges
    GPIO_PORTF_IEV_R &= ~(SW1_MASK);   	// PF4 falling edge event 
    GPIO_PORTF_ICR_R |= (SW1_MASK);    	// Clear Flag
    GPIO_PORTF_IM_R |= (SW1_MASK);     	// Arm interrupt on PF4
    
	NVIC_EN0_R |= NVIC_EN0_BTNS;
}


// ~~~~~~~~~~     GPIOPortF_Handler     ~~~~~~~~~~
// Used to acknowledge SW1 interrupt. SW1 inverts SW1_PRESSED flags.
// Input: none
// Output: none
void GPIOPortF_Handler(void){
    // simple solution to take care of button debounce: 20ms to 30ms delay
    for (uint32_t i=0;i<160000;i++) {}

    // if F0 was pressed, set SW1_pressed variable to true
    if( GPIO_PORTF_RIS_R&SW1_MASK){
        SW1_PRESSED = !SW1_PRESSED;
        GPIO_PORTF_ICR_R |= SW1_MASK;
    } 
}