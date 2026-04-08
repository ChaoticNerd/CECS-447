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
	LEFT_SLP  &= ~SLEEP_BIT;
	RIGHT_SLP &= ~SLEEP_BIT;
}

void on(void){
	LEFT_SLP  |= SLEEP_BIT;
	RIGHT_SLP |= SLEEP_BIT;
}

void backward(void){
	LEFT_DIR  &= ~FORWARD;
	RIGHT_DIR &= ~FORWARD;
}