// mode1.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles the Mode1 FSM that determines the overall mode
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso
#include "../modules/mode_manager.h"
#include <math.h>

#ifdef MCU_1

#endif
extern RingBuffer *rb_PC;
extern RingBuffer *rb_MCU;

#define MCU_1

extern void set_current_mode(int new_mode);
int current_mode1_option = 0;
extern bool EOL;
extern bool userFinished;
extern bool invalid;

extern uint8_t user_inputString[BUFFER_SIZE];

char LED_color = 'd';
uint8_t LED_brightness = 100;
char *brightness_str[3];

enum mode1_states { 
     MODE_1_MENU,
     MODE_1_COLOR,
     MODE_1_BRIGHT,
     MODE_1_EXIT,
 };

State_t mode1_fsm[4]={
     {MODE_1_MENU_VAL,   {MODE_1_MENU,       MODE_1_COLOR,       MODE_1_BRIGHT,   MODE_1_EXIT   }},
     {MODE_1_COLOR_VAL,  {MODE_1_MENU,     	 MODE_1_COLOR,       MODE_1_COLOR,    MODE_1_EXIT  	}},
     {MODE_1_BRIGHT_VAL, {MODE_1_MENU,    	 MODE_1_BRIGHT,      MODE_1_BRIGHT,   MODE_1_EXIT 	}},
     {MODE_1_EXIT_VAL,   {MODE_1_EXIT,       MODE_1_EXIT,        MODE_1_EXIT,     MODE_1_EXIT   }},
};
void mode1_manager_MCU2(){
	char user_input = UART_ReadChar(rb_MCU);
	while( user_input != (char)GRADEM){
		user_input = UART_ReadChar(rb_MCU);
	}
	current_mode1_option = MODE_1_MENU_VAL;
	set_current_mode(MAIN_MENU_VAL);
}

int mode1_manager_MCU1(){
		displayModeOneMenu_MCU1();
    while(!userFinished);
			reset_arrayInt();
			for (int i = MIN_VALID_CHAR; i < BUFFER_SIZE_READ; i++) {
				user_inputString[i] = (uint8_t)UART_ReadChar(rb_PC);
				if ((i > MIN_VALID_CHAR) && (user_inputString[i]) != INVALID_NUM) {
					invalid = INVALID_TRUE;
				}
			}
			if(invalid) {
				invalid = INVALID_FALSE;
			}
			else {
			switch(user_inputString[MIN_VALID_CHAR]){
					case 49: // Change LED
							current_mode1_option = mode1_fsm[current_mode1_option].next[MODE_1_COLOR_VAL];
							displayLEDSelect();
                            userFinished = false;
							mode1_option1();
							// while not user finished -> run option 1
							break;
					case 50: // Change brightness
							current_mode1_option = mode1_fsm[current_mode1_option].next[MODE_1_BRIGHT_VAL];
							displayBrightnessSelect();
                            userFinished = false;
							mode1_option2();
							// while not user finished -> fun option 2
							break;
					case 51: // Exit 
							userFinished = false;
							current_mode1_option = mode1_fsm[current_mode1_option].next[MODE_1_EXIT_VAL];
							LED_color = 'd';
							ActivateLED(LED_color, LED_brightness);
							break;
					default:
							userFinished = false;
							current_mode1_option = mode1_fsm[current_mode1_option].next[MODE_1_MENU_VAL];
							displayModeOneMenu_MCU1();

							break;
			}
			
		if (current_mode1_option == MODE_1_EXIT_VAL){
			current_mode1_option = MODE_1_MENU_VAL;
			set_current_mode(MAIN_MENU_VAL);
			UART5_OutChar(GRADEM);
		}
	}
			userFinished = false;
		return current_mode1_option;
}

int get_current_mode1_option(void){
	return current_mode1_option;
}


// NOTE: PUT ARRAY RESET IN MAIN

void mode1_option1(void){
	while(!userFinished){}
		if (userFinished) {
			reset_arrayInt();
    // loop through array to enter user input
    for (int i = MIN_VALID_CHAR; i < BUFFER_SIZE_READ; i++) {
        // read characters from user input
        user_inputString[i] = (uint8_t) UART_ReadChar(rb_PC);
        // if greater than first index is not 'null' (user is supposed to enter 1 char only)
        if ((i > MIN_VALID_CHAR) && (user_inputString[i] != INVALID_NUM))
            invalid = INVALID_TRUE;
				
    }
		
    // use switch case to determine color
    switch(user_inputString[MIN_VALID_CHAR]) {
        case 100: LED_color = 'd'; break;
        case 114: LED_color = 'r'; break;
        case 98:  LED_color = 'b'; break;
        case 103: LED_color = 'g'; break;
        case 99:  LED_color = 'c'; break;
        case 121: LED_color = 'y'; break;
        case 112: LED_color = 'p'; break;
        case 119: LED_color = 'w'; break;
        default: invalid = INVALID_TRUE; break;
    }
    
    // if invalid: don't update color
    if (invalid) {
        invalid = INVALID_FALSE;
        reset_arrayInt();
    }
    else {
        // if not, update color
        ActivateLED(LED_color, LED_brightness);
    }
    displayCurrentColor();

	}
}

// output menu outside function
void mode1_option2(void){
		while(!userFinished){}
    if (userFinished) {
			reset_arrayInt();
        // create string to store brightness bc it sends 1 value at a time
        // --> initialize all values to 255 since it won't be used
        uint8_t digit_power = DIGIT_POWER_RESET;
			// 
        uint16_t temp_brightness = TEMP_BRIGHTNESS_RESET; // this one is for adjusting for extra large values

        // loop through array to read all entered values
        for (int i = MIN_VALID_CHAR; i < BUFFER_SIZE_READ; i++) {
            // read characters from user input
            user_inputString[i] = (uint8_t) UART_ReadChar(rb_PC);
            if ( (((user_inputString[i] - CHAR_TO_NUM) < MIN_DIGIT) || ((user_inputString[i] - CHAR_TO_NUM) > MAX_DIGIT) 
                // or check if more than 3 chars
                || ((i > MAX_BRIGHT_CHARS)) )
                // then check if any char isn't 'null'
                && (user_inputString[i] != INVALID_NUM)
                )
                invalid = INVALID_TRUE; // set invalid to true
        }

        // if invalid was found: set invalid to 0 and skip updating brightness
        if (invalid) {
            invalid = INVALID_FALSE;
        }
        else {
            // loop through array backwards to read from ones digit first
            // note that 0 => 48, 9 => 57, subtract 48 to get numerical value from char
            for (int i = MAX_BRIGHT_CHARS; i >= MIN_BRIGHT_CHARS; i--) { 
                // if not a null value, add to brightness
                if (user_inputString[i] != INVALID_NUM)
                    temp_brightness += (uint16_t) (user_inputString[i] - CHAR_TO_NUM) * pow(10,digit_power++);
            }

            // then do a final brightness check: if invalid number
						
            if  ((temp_brightness >= BRIGHT_MIN) && (temp_brightness <= BRIGHT_MAX)) {
                for (int i = MIN_BRIGHT_CHARS; i <= MAX_BRIGHT_CHARS; i++) {
                    *brightness_str[i] = (char) user_inputString[i];
                }
                // update brightness value and hardware brightness
                LED_brightness = temp_brightness;
                ActivateLED(LED_color, LED_brightness);
								
            }
						
        }
				displayLEDBrightness(LED_brightness);
    }
}


char get_current_color(void) {
	return LED_color;
}