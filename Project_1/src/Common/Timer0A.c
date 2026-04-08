// Timer0A.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "Timer0A.h"
#include <stdint.h>


// ~~~~~~~~~~     Timer0A_Init     ~~~~~~~~~~
// Used to initialize Timer0A in 32-bit periodic countdown with interrupt priority 5.
// Input: none
// Output: none
void Timer0A_Init(void){
    SYSCTL_RCGCTIMER_R |= TIMER0_SETUP;          // activate TIMER0
    while((SYSCTL_RCGCTIMER_R & 0x01)==0){}; 		 // wait for Timer0 to set up

    TIMER0_CTL_R &= ~TIMER0_ENABLE;              // turn off Timer0A
    TIMER0_CFG_R = TIMER0_32BIT;                 // set Timer0A reload to 32-bit size
    TIMER0_TAMR_R = TIMER0_PCD;                  // set Timer0A mode to periodic countdown
    TIMER0_TAPR_R = TIMER0_PRESCALE;             // set Timer0A prescale to 0

    TIMER0_ICR_R = TIMER0_ENABLE;                // clear interrupt flag
    TIMER0_IMR_R |= TIMER0_ENABLE;               // arm Timer0A timeout interrupt

    // set priority for IRQ 19 to priority 5
    NVIC_PRI4_R = (NVIC_PRI4_R & TIMER0_PRIORITY_CLEAR) | TIMER0_PRIORITY_SET;

    NVIC_EN0_R |= TIMER0A_IRQ; // enable IRQ bit 19 in NVIC for Timer0A
}

// ~~~~~~~~~~     Timer0A_Start     ~~~~~~~~~~
// Used to start Timer0A countdown.
// Input: none
// Output: none
void Timer0A_Start(void){
    TIMER0_CTL_R |= TIMER0_ENABLE; // turn on Timer0A
}

// ~~~~~~~~~~     Timer0A_Change_Reload     ~~~~~~~~~~
// Used to change Timer0A reload value. Used to change sound frequency.
// Input: uint32_t reload
// Output: none
void Timer0A_Change_Reload(uint32_t reload){
    TIMER0_TAILR_R = reload - 1; // change reload to inputted reload value - 1
}

// ~~~~~~~~~~     Timer0A_Stop     ~~~~~~~~~~
// Used to stop Timer0A countdown.
// Input: none
// Output: none
void Timer0A_Stop(void){
    TIMER0_CTL_R &= ~TIMER0_ENABLE;	// turn off Timer0A
}