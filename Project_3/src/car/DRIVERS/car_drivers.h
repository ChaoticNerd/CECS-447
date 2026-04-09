// car_drivers.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 3
// Driver description: Enables GPIO Pins C67 and D67 (6 - dir, 7 SLP)
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
// main contributor: Natasha Kho
#include "../../tm4c123gh6pm.h"

void car_control_Init(void);

#define PORT67_PINS 0xC0
#define PORT67_BITS 0xFF000000