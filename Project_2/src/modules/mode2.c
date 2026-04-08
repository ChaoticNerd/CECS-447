// mode2.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles the Mode2 FSM that determines the overall mode
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso
#include "../modules/mode_manager.h"

extern void set_current_mode(int new_mode);
int current_mode2_option = 0;
int current_color = 1;
extern bool SW1_pressed;
extern bool SW2_pressed;
extern char LED_color;
extern uint8_t LED_brightness;
extern bool EOL;
extern bool userFinished;
char MCU1_read = 0;
char MCU2_read = 0;

extern RingBuffer *rb_PC;
extern RingBuffer *rb_MCU;
extern void WaitForInterrupt();

uint8_t getColour_mode2;

char LEDcolor_array[NUM_COLORS] = {'d','r','g','b','y','c','p','w'};

enum mode2_states { 
    MCU1_TO_MCU2,
    MCU2_TO_MCU1,
};

State_t mode2_fsm[2]={
    { MCU1_TO_MCU2_VAL, {MCU2_TO_MCU1,      MCU2_TO_MCU1}},
    { MCU2_TO_MCU1_VAL, {MCU1_TO_MCU2,      MCU1_TO_MCU2}},
};


int mode2_manager(void){
	#ifdef MCU_1
		while(get_current_mode() == MODE_2_VAL) {
			
			if (current_mode2_option == MCU1_TO_MCU2_VAL) {
				if (SW2_pressed){
						updateLED();
						displayCurrentColor();
						SW2_pressed = false;
				}
				if (SW1_pressed) {
					displayModeTwo_MCU1_Cont();
					sendLED_MCU1();
					current_mode2_option = mode2_fsm[current_mode2_option].next[SW1_pressed];
					SW1_pressed = false;
				}
			}
			else if (current_mode2_option == MCU2_TO_MCU1_VAL) {
				receiveLED(MCU2_read);
			}
			
			if(userFinished) {
				char c = UART_ReadChar(rb_PC);		
				// initlaize LED color to dark upon entry
				if (c == '^'){
						current_mode2_option = MCU1_TO_MCU2_VAL;
						UART5_OutChar(GRADEM); // tell MCU_2 to exit to main menu
						current_color = COLOR_RESET;
						updateLED();
						set_current_mode(MAIN_MENU_VAL);
						userFinished = false;
						ClearBuffer(rb_PC);
						return -1;
				}
			}
			
			MCU2_read = UART_ReadChar(rb_MCU);
		}
	#endif

	#ifdef MCU_2
		while(get_current_mode() == MODE_2_VAL) {
			
			if (current_mode2_option == MCU2_TO_MCU1_VAL) {
				if (SW2_pressed){
						updateLED();
						displayCurrentColor();
						SW2_pressed = false;
				}
				if (SW1_pressed) {
					displayModeTwoMenu_MCU2_Initial();
					displayCurrentColor();
					sendLED_MCU2();
					current_mode2_option = mode2_fsm[current_mode2_option].next[SW1_pressed];
					SW1_pressed = false;
				}
			}
			else if (current_mode2_option == MCU1_TO_MCU2_VAL) {
				receiveLED(MCU1_read);
			}
			
			MCU1_read = UART_ReadChar(rb_MCU);
			if(MCU1_read == (char) GRADEM){
				current_mode2_option = MCU1_TO_MCU2_VAL;
				current_color = COLOR_RESET;
				updateLED();
				set_current_mode(MAIN_MENU_VAL);
				return -1;
			}
		}
	#endif
		
		return 0;
}


void sendLED_MCU1(void) {
    if (current_mode2_option == MCU1_TO_MCU2_VAL) {
				UART5_OutChar((uint8_t) FLAG);
        UART5_OutChar((uint8_t) current_color);
		}
}

void sendLED_MCU2(void){
	if(current_mode2_option == MCU1_TO_MCU2_VAL) {
		UART7_OutChar((uint8_t) FLAG);
		UART7_OutChar((uint8_t) current_color);
	}
}



void updateLED(void) {
    // update LED color, update current color
    LED_color = LEDcolor_array[(current_color++) % NUM_COLORS];
    ActivateLED(LED_color, LED_brightness);

}

// heewwo hewwo
int get_current_mode2_option(void){
	return current_mode2_option;
}

void receiveLED(char MCUin) {
	if (MCUin == (char) FLAG)  {
		WaitForInterrupt();
		current_color = UART_ReadChar(rb_MCU) - 1;
		updateLED();
		current_mode2_option = mode2_fsm[current_mode2_option].next[SW1_pressed];
		
		#ifdef MCU_1
		displayModeTwoMenu_MCU1_Initial();
		#endif
		
		#ifdef MCU_2
		displayModeTwo_MCU2_Cont();
		displayCurrentColor();
		#endif
		
		SW1_pressed = false;
		SW2_pressed = false;
	}
}