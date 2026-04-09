// car_movements.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: Handles movement functions for car
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
// main contributor: Natasha Kho

#include "../../tm4c123gh6pm.h"

// initialize PD67 - right side - dir/slp 
// initialize PC67 - left side - dir/slp

#define SLEEP_BIT 0x80

#define LEFT_DIR    (*((volatile unsigned long *)0x40007100)) // PD6
#define RIGHT_DIR   (*((volatile unsigned long *)0x40006100)) // PC6

#define LEFT_SLP    (*((volatile unsigned long *)0x40007200)) // PD7
#define RIGHT_SLP   (*((volatile unsigned long *)0x40006200)) // PC7

// Which wheels to turn on
#define BOTH_WHEELS 0xC0
#define LEFT_WHEEL 0x40
#define RIGHT_WHEEL 0x80

// Directions
#define FORWARD 0x40
// Backwards is just reverse of forwards


void forward(void);
void backward(void);
void off(void);
void on(void);
void pivot_left(void);
void pivot_right(void);