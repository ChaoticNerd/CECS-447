// LED.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Controls on-board LEDs
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho

#ifndef LED_H
#include <stdint.h>
#include "../../tm4c123gh6pm.h"
#define LED         (*((volatile unsigned long *) 0x40025038))  // use onboard three LEDs: PF321

// LED COLORS
#define  RED     0x02
#define  BLUE    0x04
#define  GREEN   0x08
#define  PINK    0x06
#define  YELLOW  0x0A
#define  CYAN    0x0C
#define  WHITE   0x0E
#define  DARK    0x00


// Function prototypes
void LED_Init(void);
void change_LED(uint8_t color);
#endif

