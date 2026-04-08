// gpio_btn.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "../tm4c123gh6pm.h"
#include "gpio_btn.h"

// ~~~~~~~~~~     LED_Init     ~~~~~~~~~~
// Used to initialize onboard LEDS. Only used for testing
// Input: none
// Output: none
void LED_init(void){
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0){};
		
    GPIO_PORTF_AMSEL_R &= ~0x0E;      // 3) disable analog function
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // 4) GPIO clear bit PCTL  
    GPIO_PORTF_DIR_R |= 0x0E;         // 6) PF1-PF3 output
    GPIO_PORTF_AFSEL_R &= ~0x0E;      // 7) no alternate function     
    GPIO_PORTF_DEN_R |= 0x0E;         // 8) enable digital pins PF3-PF1
    LED = 0x00;                       // Turn off all LEDs.
}

// ~~~~~~~~~~     BTNS_init     ~~~~~~~~~~
// Used to initialize onboard buttons and external buttons. Calls both initializtion functions.
// Input: none
// Output: none
void BTNS_Init(void){
		// call board buttons init and external buttons init
    Board_BTNS_init();
    Piano_keys_init();
}

// ~~~~~~~~~~     Board_BTNS_init     ~~~~~~~~~~
// Used to initialize onboard Buttons. Set buttons to input, used to change between piano or autoplay mode
// for PF4 and octave or song for PF0.
// Input: none
// Output: none
void Board_BTNS_init(void){
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

    NVIC_EN0_R = PORTF_IRQ;   				// (h) enable Port F edge interrupt
}

// ~~~~~~~~~~     Piano_keys_init     ~~~~~~~~~~
// Used to initialize external Buttons. Set buttons to input, used to change play piano notes
// depending on which button is pressed.
// Input: none
// Output: none
void Piano_keys_init(void){
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOE)!=SYSCTL_RCGC2_GPIOE){}
		
	GPIO_PORTE_CR_R |= EXTERNAL_BTNS_IN;         // allow changes to PE
    GPIO_PORTE_AMSEL_R &= ~EXTERNAL_BTNS_IN;     // disable analog function
    GPIO_PORTE_PCTL_R &= ~EXTERNAL_BTNS_CLEAR_PCTL; 	// GPIO clear bit PCTL  
    GPIO_PORTE_DIR_R &= ~EXTERNAL_BTNS_IN;       // PE input   
    GPIO_PORTE_AFSEL_R &= ~EXTERNAL_BTNS_IN;     // no alternate function
    GPIO_PORTE_PUR_R |= EXTERNAL_BTNS_PUR;          	// disable pullup resistors on PE
    GPIO_PORTE_DEN_R |= EXTERNAL_BTNS_IN;        // enable digital pins PE

    GPIO_PORTE_IS_R &= ~(C_KEY|D_KEY|F_KEY|E_KEY);    // PE0123 is edge-sensitive
    GPIO_PORTE_IBE_R |= (C_KEY|D_KEY|F_KEY|E_KEY);   // PE0123 is both edges
    GPIO_PORTE_ICR_R |= (C_KEY|D_KEY|F_KEY|E_KEY);    // Clear Flag0
    GPIO_PORTE_IM_R |= (C_KEY|D_KEY|F_KEY|E_KEY);     // Arm interrupt on PE0123

    NVIC_EN0_R = PORTE_IRQ;   				// (h) enable Port E edge interrupt
}
