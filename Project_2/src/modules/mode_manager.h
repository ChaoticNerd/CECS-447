// mode_manager.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles Selecting mode for MCU 1 and MCU 2
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#ifndef MODE_MANAGER_H

#include <stdint.h>
#include "../tm4c123gh6pm.h"
#include "../drivers/UART0.h"
#include "../drivers/UART5.h"
#include "../drivers/UART7.h"
#include "../drivers/Switches.h"
#include "../drivers/PWM.h"
#include "../modules/display.h"
#include "../modules/ring_buffer.h"
#include "../config.h"
#include <stdbool.h> 
#include "../config.h"

#define INVALID_TRUE        1
#define INVALID_FALSE       0

#define NUM_STATES	    4
#define MAIN_MENU_VAL   0
#define MODE_1_VAL      1
#define MODE_2_VAL      2
#define MODE_3_VAL      3
#define INVALID_CHAR    0xFF
#define MIN_VALID_CHAR      0

int mode_manager_MCU1(char user_input);
void mode_manager_MCU2(char user_input);
int get_current_mode(void);

void set_current_mode(int);
void reset_arrayInt(void);	
char get_current_color(void);

struct State {
    uint8_t select;
    uint8_t next[NUM_STATES];
};
typedef const struct State State_t;

																				

// MODE ONE STUFF
#define MODE_1_MENU_VAL     0
#define MODE_1_COLOR_VAL    1
#define MODE_1_BRIGHT_VAL   2
#define MODE_1_EXIT_VAL     3
#define INVALID_NUM         255
#define BUFFER_SIZE_READ    30
#define BRIGHT_MIN          0
#define BRIGHT_MAX          100
#define MIN_BRIGHT_CHARS    0
#define MAX_BRIGHT_CHARS    2
#define CHAR_TO_NUM         48
#define MIN_DIGIT             0
#define MAX_DIGIT             9
#define DIGIT_POWER_RESET       0
#define TEMP_BRIGHTNESS_RESET   0

int mode1_manager_MCU1(void);
void mode1_manager_MCU2(void);
int get_current_mode1_option(void);

void mode1_option1(void);

void mode1_option2(void);




// MODE TWO STUFF
#define MCU1_TO_MCU2_VAL      0
#define MCU2_TO_MCU1_VAL      1
#define COLOR_RESET           0
#define NUM_COLORS            8

int mode2_manager(void);

int get_current_mode2_option(void);

void updateLED(void);

void sendLED_MCU1(void);
void sendLED_MCU2(void);
void receiveLED(char MCUin);


// MODE THREE STUFF
// #include "mode_manager.h"

int mode3_manager_MCU1(void);

int mode3_manager_MCU2(void);

int get_current_mode3_option(void);

int UART5_RX(void);

void UART5_TX(void);

int UART7_RX(void);

void UART7_TX(void);
#endif