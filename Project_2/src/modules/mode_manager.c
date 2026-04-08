// mode_manager.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles the Top level FSM that determines the overall mode
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso


// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "mode_manager.h"
#include <stdbool.h>

extern RingBuffer *rb_PC;
extern RingBuffer *rb_MCU;
int current_mode = 0;
bool invalid = 0;
 
extern bool EOL;
enum states { 
    MAIN_MENU,
    MODE_1,
    MODE_2,
    MODE_3,
};

uint8_t user_inputString[BUFFER_SIZE] = {255, 255,  255, 255, 255, 255, 255, 255, 255, 255,
                                        255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
                                        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

State_t mode_fsm[NUM_STATES]={
    {MAIN_MENU_VAL, {MAIN_MENU, MODE_1,     MODE_2,     MODE_3      }},
    {MODE_1_VAL,    {MAIN_MENU, MODE_1,  	MODE_1,     MODE_1      }},
    {MODE_2_VAL,    {MAIN_MENU, MODE_2,     MODE_2,  	MODE_2      }},
    {MODE_3_VAL,    {MAIN_MENU, MODE_3,     MODE_3,     MODE_3      }},
};


#ifdef MCU_1
//// initialize user input in main as main_menu
int mode_manager_MCU1(char user_input){
    
    switch(user_input){
        case '1': // mode 1 menu
					
			current_mode = mode_fsm[current_mode].next[MODE_1_VAL];
			UART5_OutChar(ANGRY); // telling MCU_2 to STFU I HAVE YAPPING STICK
            //displayModeOneMenu_MCU1();
            while(current_mode == MODE_1_VAL)
                mode1_manager_MCU1();
            break;
        case '2': // mode 2 menu
			displayModeTwoMenu_MCU1_Initial();
			current_mode = mode_fsm[current_mode].next[MODE_2_VAL];
            UART5_OutChar(BETA); // telling MCU_2 to GET THEIR BITCHASS READY FOR COLORS
            while(current_mode == MODE_2_VAL)
                mode2_manager();
            break;
        case '3': // mode 3 menu
            displayModeThreeMenu_MCU1(); // MCU2 has own Manager and display differently
			current_mode = mode_fsm[current_mode].next[MODE_3_VAL];
            UART5_OutChar(FLAG); // telling MCU_2 to FUCKING LISTEN, DUMBASS
            mode3_manager_MCU1();
            break;
        case ((char) INVALID_CHAR): // edge case where the user doesn't put anything but triggers SW interrupt
            break; // just pass through. otherwise it will spam menu continuously
        default:
            current_mode = mode_fsm[current_mode].next[MAIN_MENU_VAL];
            displayTryAgainInput();
            break;
    }
		ClearBuffer(rb_PC);
	displayMainMenu_MCU1();
    return current_mode;
}
#endif

#ifdef MCU_2
void mode_manager_MCU2(char user_input){
    switch(user_input){
        case (char)ANGRY: 
            current_mode = mode_fsm[current_mode].next[MODE_1_VAL];
			mode1_manager_MCU2();
            break;
            
        case (char)BETA:
            displayModeTwoMenu_MCU2_Initial();
            current_mode = mode_fsm[current_mode].next[MODE_2_VAL];
			mode2_manager();
            break;

        case (char)FLAG:
            displayModeThreeMenu_MCU2();
            current_mode = mode_fsm[current_mode].next[MODE_3_VAL];
			UART0_OutCRLF();
            mode3_manager_MCU2();
            break;

        default: 
            current_mode = mode_fsm[current_mode].next[MAIN_MENU_VAL];
            displayTryAgainInput();
            break;
    }
		ClearBuffer(rb_PC);
}

#endif

int get_current_mode(void){
	return current_mode;
}

void set_current_mode(int new_mode){
    current_mode = (uint8_t) mode_fsm[current_mode].next[new_mode];
}



void reset_arrayInt(void) {
    for(int i = 0; i < BUFFER_SIZE; i++) {
        user_inputString[i] = 255;
    }
}