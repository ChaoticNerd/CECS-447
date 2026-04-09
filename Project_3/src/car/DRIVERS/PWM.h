// PWM.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Controls L and R PWM for car motors
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho

#ifndef PWM_H
#include "../../tm4c123gh6pm.h"
//////////////////////2. Declarations Section////////////////////////////////
									////////// Constants //////////
// Constant definitions based on the following hardware interface:
// System clock is 16MHz.
// TOTAL PERIOD 100
// 20 30 50
#define TOTAL_PERIOD 100 //  16MHz/1000=16000
#define PORT01_PINS 0x03
#define PORT01_CLEAR_PCTL 0x000000FF
#define PORT01_SET_PCTL 0x00000044

#define PWM0_3_CTL 0x00000002
#define PWM0_3_GENA 0xC8
#define PWM0_3_GENB 0xC08

#define SYSCTL_RCGCPWM0 0x01
#define SYSCTL_RCC_NO_DIV 0x00100000

#define EN_PWM0_3 0x00000001
// PB7632 are used for direction control on L298.
// Motor 1 is connected to the left wheel, Motor 2 is connected to the right wheel.


//Wheels 
// #define BOTH_WHEEL 0x0000000C;
// #define RIGHT_WHEEL 0x00000008;
// #define LEFT_WHEEL 0x00000004;
//////////////////////1. Declarations Section////////////////////////////////
////////// Function Prototypes //////////
// Dependency: None
// Inputs: None
// Outputs: None
// Description: 
void PWM1_PD01_Init(void);

// Dependency: PWM_PB76_Init()
// Inputs: 
//	duty_L is the value corresponding to the duty cycle of the left wheel
//	duty_R is the value corresponding to the duty cycle of the right wheel
// Outputs: None 
// Description: Changes the duty cycles of PB76 by changing the CMP registers
void PWM_Duty(unsigned long duty_L, unsigned long duty_R);
/////////////////////////////////////////////////////////////////////////////
#endif