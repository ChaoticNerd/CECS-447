// car_movements.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Driver description: Handles movement functions for car
// Team #: 6
// Team members: Natasha Kho, Justin Narciso, Hanna Estrada
// main contributor: Natasha Kho

#include "car_movements.h"

// both WHEELS = 0XC0
void forward(void){
	LEFT_DIR |= FORWARD;
	RIGHT_DIR |= FORWARD;
}

void off(void){
	PWM0_ENABLE_R &= ~BOTH_WHEELS;
}

void on(void){
	PWM0_ENABLE_R |= BOTH_WHEELS;
	LEFT_SLP  |= SLEEP_BIT;
	RIGHT_SLP |= SLEEP_BIT;
}

void backward(void){
	LEFT_DIR  &= ~FORWARD;
	RIGHT_DIR &= ~FORWARD;
}

void pivot_right(void){
	LEFT_DIR  &= ~FORWARD;
	RIGHT_DIR |= FORWARD;
}

void pivot_left(void){
	LEFT_DIR  |= FORWARD;
	RIGHT_DIR &= ~FORWARD;
}