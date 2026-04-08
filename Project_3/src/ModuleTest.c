// ModuleTest.c
// Course number:
// Term: 
// Project number: 
// Module description: 
// A brief summary on modules tested in this module test file,
// including module list, responsibility and team member assignment
// Team #:
// Team members:


// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
// Example:
// #include module1_driver.h

//#include "CAR/DRIVERS/LED.h"
//#include "CAR/DRIVERS/SWITCHES.h"
//#include "CAR/DRIVERS/PWM.h"
//#include "CAR/modules/FSM.h"
#include "car/config.h"
// preprocessor directives for module name
// Example:
// #define MODULE_1_TEST
// #define LED_TEST
// #define SWITCHES_TEST
 #define PWM_LEFT_TEST
// #define PWM_RIGHT_TEST
// #define FSM_MODE1_TEST
// #define FSM_MODE2_TEST
// #define BLT_TEST

/*
#if defined()

#endif
*/

// functions prototypes
void System_Init(void);
void Delay500ms(void);
extern void EnableInterrupts();
extern void WaitForInterrupt();
extern void DisableInterrupts();
extern void forward(unsigned long);
extern void backward(unsigned long);

// Module test function prototypes
#if defined(MODULE_1_TEST)
void Module_1_Test(void);
#endif

#if defined(LED_TEST)
change_LED(DARK);
#endif

#if defined(SWITCHES_TEST)
extern bool SW1_PRESSED;
#endif

#if defined(PWM_LEFT_TEST)

#endif

#if defined(PWM_RIGHT_TEST)

#endif

#if defined(FSM_MODE1_TEST)
extern bool SW1_PRESSED;
extern int current_mode1;
#endif

#if defined(FSM_MODE2_TEST)
extern bool SW1_PRESSED;
extern int current_mode2;
#endif

#if defined(BLT_TEST)
uint8_t BluetoothResponse[30];
#endif

int main(void){
  System_Init();
  while(1){
    // Call individual module test functions here
	// Example:
	#if defined(MODULE_1_TEST)
	Module_1_Test();
	#endif

  #if defined(LED_TEST)
    change_LED(RED);
    Delay500ms();

    change_LED(BLUE);
    Delay500ms();

    change_LED(GREEN);
    Delay500ms();

    change_LED(PINK);
    Delay500ms();

    change_LED(CYAN);
    Delay500ms();

    change_LED(YELLOW);
    Delay500ms();

    change_LED(WHITE);
    Delay500ms();

    change_LED(DARK);
    Delay500ms();
    Delay500ms();
  #endif

  #if defined(SWITCHES_TEST)

    if (SW1_PRESSED){
      change_LED(BLUE);
      SW1_PRESSED = false;
    } else {
      change_LED(GREEN);
    }
    Delay500ms();
    
  #endif

  #ifdef PWM_LEFT_TEST
    forward(1);
    Delay500ms();
    backward(1);
    Delay500ms();
  #endif

  #if defined(PWM_RIGHT_TEST)
    PWM_Duty(0,9000);
    Delay500ms();
    PWM_Duty(0,5000);
    Delay500ms();
  #endif

  #if defined(FSM_MODE1_TEST)
  mode_one_manager();
    switch(current_mode1){
      case 0: 
        change_LED(RED); // in idle
      break;
      case 1: 
        change_LED(BLUE); // in '8'
      break;
      case 2: 
        change_LED(GREEN); // in 'C'
      break;
      case 3: 
        change_LED(PINK); // in 'S'
      break;
      case 4:
        change_LED(YELLOW); // in 'Z'
      break;
    }
  #endif

  #if defined(FSM_MODE2_TEST)
  mode_two_manager();
    switch(current_mode2){
      case 0: 
        change_LED(RED); // in STOP
      break;
      case 1: 
        change_LED(BLUE); // in FORWARD
      break;
      case 2: 
        change_LED(GREEN); // in BACKWARD
      break;
      case 3: 
        change_LED(PINK); // in LEFT
      break;
      case 4:
        change_LED(YELLOW); // in RIGHT
      break;
      case 5: 
        change_LED(CYAN); // in SPEEDUP
      break;
      case 6:
        change_LED(WHITE); // in SPEEDDOWN
      break;
    }

  #endif

  #if defined(BLT_TEST)
    //uint8_t c = UART1_InChar(); // use BLT inString with BluetoothResponse
    UART1_InString(BluetoothResponse);
    switch(BluetoothResponse[0]){
      case (uint8_t) 'R':
        change_LED(RED);
				Delay500ms();
        break;
      case (uint8_t) 'G':
        change_LED(GREEN);
				Delay500ms();
        break;
      case (uint8_t) 'B':
        change_LED(BLUE);
				Delay500ms();
        break;
      default:
        change_LED(DARK);
				Delay500ms();
        break;
    }
		Delay500ms();
    // smthn case statement based on the bluetooth buffer
  #endif
  }
}

void System_Init(void){
  // Example:
  DisableInterrupts();
  #if defined(MODULE_1_TEST)
  Module_1_Init();
  #endif	

  #if defined(LED_TEST)
    LED_init();

  #endif

  #if defined(SWITCHES_TEST)
    LED_init();
    SWITCHES_init();
  #endif

  #ifdef PWM_LEFT_TEST
    PWM1_PD01_Init();
	car_control_Init();
  #endif

  #if defined(PWM_RIGHT_TEST)
	car_control_Init();
    PWM1_PD01_Init();
  #endif

  #if defined(FSM_MODE1_TEST)
    LED_init();
    UART1_init();
    Switches_init();
  #endif

  #if defined(FSM_MODE2_TEST)
    LED_init();
    UART1_init();
    Switches_init();
  #endif

  #if defined(BLT_TEST)
    UART1_Init();
    LED_init();
  #endif
  EnableInterrupts();
}

// Module test function definitions
#if defined(MODULE_1_TEST)
void Module_1_Test(void){
}
#endif

#if defined(LED_TEST)

#endif

#if defined(SWITCHES_TEST)

#endif

#if defined(PWM_LEFT_TEST)

#endif

#if defined(PWM_RIGHT_TEST)

#endif

#if defined(FSM_MODE1_TEST)

#endif

#if defined(FSM_MODE2_TEST)

#endif



// software delay
void Delay500ms(void){
	unsigned long volatile time;
  time = 14545*50;  // 10msec (*50 to get .5 sec)
  while(time){
		time--;
  }
}