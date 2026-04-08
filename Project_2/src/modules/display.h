
// display.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles displaying menu for each MCU
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso


// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "../drivers/UART0.h"
#include "../config.h"
#include <stdio.h>
extern uint8_t get_LED_color(void);
extern char get_current_color(void);
char* getColor(void);

void displayMainMenu_MCU1(void);
void displayMainMenu_MCU2(void);

void displayModeOneMenu_MCU1(void);
void displayModeOneMenu_MCU2(void);

void displayModeTwoMenu_MCU1_Initial(void);
void displayModeTwoMenu_MCU2_Initial(void);
void displayModeTwo_MCU1_Cont(void);
void displayModeTwo_MCU2_Cont(void);

void displayModeThreeMenu_MCU1(void);
void displayModeThreeMenu_MCU2(void);

void displayLEDSelect(void);
void displayBrightnessSelect(void);

void displayTryAgainInput(void);
void displayCurrentColor(void);
void displayLEDBrightness(uint8_t);

char* getColor(void);