// main.c
// Course number: 447
// Term: Spring 2026
// Project number: 3
// Project description: Bluetooth controlled car 
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso 
// Main contributer: Natasha Kho

// Header files needed for this program
#include "config.h"


// global variables
extern bool SW1_PRESSED;
extern void mode_one_manager(void);
extern void mode_two_manager(void);
extern void DisableInterrupts();
extern void EnableInterrupts();

// function prototypes
void System_Init(void);

int main(void){	
  System_Init();
  
  while(1){
    if(!SW1_PRESSED){ // 0 is mode 1
        mode_one_manager();
    }else if(SW1_PRESSED){ // 1 is mode 2
        mode_two_manager();
    }
  }
}

void System_Init(void) {
    DisableInterrupts();
    LED_Init();
    PWM1_PD01_Init();
    Switch_Init();
    UART1_Init();
    car_control_Init();
    EnableInterrupts();
}
