// Switches.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles SW1 and SW2 onboard buttons; Justin Narciso, Natasha Kho
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
#include <stdint.h>
#include <stdbool.h>
#include "../tm4c123gh6pm.h"
#include "../config.h"

#define BOARD_BTNS  (*((volatile unsigned long *) 0x40025040)) // On-board buttons on PF0 (SW2), PF4 (SW1)


#define SW1_MASK                0x10				// PF0
#define SW2_MASK                0x01				// PF4
#define NVIC_EN0_BTNS           0x40000000
#define BOARD_BTNS_IN           0x11	
#define UNLOCK_PORTF0           0x4C4F434B
#define BOARD_BTNS_CLEAR_PCTL   0x000F000F 
#define BOARD_BTNS_PUR          0x11 


void Board_BTNS_Init(void);