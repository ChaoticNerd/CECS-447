// DAC.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include <stdint.h>
#include "../tm4c123gh6pm.h"

#define DAC (*((volatile unsigned long *)0x4000733C)) // PD012367
	
#define DAC_Pins			0xCF
#define DAC_PCTL			0xFF00FFFF

// function templates
void DAC_Init(void);
void DAC_Out(uint8_t data);