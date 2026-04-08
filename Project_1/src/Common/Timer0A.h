// Timer0A.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
#include "../tm4c123gh6pm.h"
#include <stdint.h>

// Function Prototypes
void Timer0A_Init(void);
void Timer0A_Start(void);
void Timer0A_Change_Reload(uint32_t reload);
void Timer0A_Stop(void);

// Definitions
#define TIMER0_SETUP	0x01
#define TIMER0_CLEAR	0x00
#define TIMER0_32BIT	0x00
#define TIMER0_PCD		0x02
#define TIMER0_PRESCALE 0
#define TIMER0_ENABLE	0x00000001

#define TIMER0_PRIORITY_CLEAR 0x1FFFFFFF
#define TIMER0_PRIORITY_SET 0xA0000000
#define TIMER0A_IRQ 0x00080000