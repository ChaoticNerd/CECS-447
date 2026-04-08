// mode3.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles the Mode3 FSM for both MCU
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso
#include "mode_manager.h"

extern void set_current_mode(int new_mode);
extern bool SW1_pressed;
extern bool SW2_pressed;
extern bool EOL;
extern bool userFinished;
extern RingBuffer *rb_PC;
extern RingBuffer *rb_MCU;

char mode3_inputString[30];
unsigned char char_check;

enum mode3_states { 
    MCU1_TO_MCU2,
    MCU2_TO_MCU1,
};

State_t mode3_fsm[2]={
    { MCU1_TO_MCU2_VAL, {MCU2_TO_MCU1,      MCU2_TO_MCU1}},
    { MCU2_TO_MCU1_VAL, {MCU1_TO_MCU2,      MCU1_TO_MCU2}},
};

int current_mode3_option;

#ifdef MCU_1
int mode3_manager_MCU1(void){
    while(get_current_mode() == MODE_3_VAL){
      if(current_mode3_option == mode3_fsm[MCU1_TO_MCU2_VAL].select){
                UART5_TX();
			}
			else if(current_mode3_option == mode3_fsm[MCU2_TO_MCU1_VAL].select){
							UART5_RX();
			}
    }
        return -1;
}
 #endif


#ifdef MCU_2
int mode3_manager_MCU2(void){
    while(get_current_mode() == MODE_3_VAL){
        if(current_mode3_option == mode3_fsm[MCU1_TO_MCU2_VAL].select){
						UART7_RX();
				}
				else if(current_mode3_option == mode3_fsm[MCU2_TO_MCU1_VAL].select){
						UART7_TX();
				}
    }
        return -1;
}
#endif

void UART5_TX(void){
			if(userFinished){ // send msg
					UART5_OutChar(HELI);        // MCU2 Transmit now
					UART5_OutBuffer(rb_PC);            
					current_mode3_option = mode3_fsm[current_mode3_option].next[1];
					userFinished = false;
			}
			
			if(SW1_pressed){ //goodbye
					UART5_OutChar(GRADEM);
					current_mode3_option = MCU1_TO_MCU2_VAL;
					SW1_pressed = false;
					userFinished = false;
					set_current_mode(MAIN_MENU_VAL);
			}
			if(UART_ReadChar(rb_MCU)== (char)GRADEM){
					current_mode3_option = MCU1_TO_MCU2_VAL;
					userFinished = false;
					set_current_mode(MAIN_MENU_VAL);
			}

}

void UART7_TX(void){
		if(userFinished){ // send msg
				UART7_OutChar(GAMMAL);         // MCU1 Transmit now
				UART7_OutBuffer(rb_PC);            
				current_mode3_option = mode3_fsm[current_mode3_option].next[1];
				userFinished = false;
		}
		
		if(SW1_pressed){ //goodbye
				UART7_OutChar(GRADEM);
				current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
		}
		if(UART_ReadChar(rb_MCU)== (char)GRADEM){
				current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
		}

}

int UART5_RX(void){
    // WAIT UNTIL FLAG IS SENT
    char flagTX = UART_ReadChar(rb_MCU);
    while(flagTX != (char)GAMMAL){
			flagTX = UART_ReadChar(rb_MCU);
			if(SW1_pressed){ //goodbye
				UART5_OutChar(GRADEM);
				current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
				ClearBuffer(rb_PC);
				return 0;
		}
		if(flagTX == (char)GRADEM){
				current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
				ClearBuffer(rb_PC);
				return 0;
		}	
		}
		
    for (uint32_t i=0;i<160000;i++) {}
			
    // FLAG IS SENT NOW, TIME TO 	DISPLAY
    UART0_OutBuffer(rb_MCU);
		
        
    // change state to TX
    current_mode3_option = mode3_fsm[current_mode3_option].next[1];
		ClearBuffer(rb_PC);
    return 1;
}

int UART7_RX(void){
    // WAIT UNTIL FLAG IS SENT
    char flagTX = UART_ReadChar(rb_MCU);
    while(flagTX != (char)HELI){
			flagTX = UART_ReadChar(rb_MCU);
			if(SW1_pressed){ //goodbye
				UART7_OutChar(GRADEM);
				current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
				ClearBuffer(rb_PC);
				return 0;
			}
			if(flagTX == (char)GRADEM){
					current_mode3_option = MCU1_TO_MCU2_VAL;
				SW1_pressed = false;
				userFinished = false;
				set_current_mode(MAIN_MENU_VAL);
				ClearBuffer(rb_PC);
				return 0;
			}
		}
		
		
    // simple solution to take care of button debounce: 20ms to 30ms delay
    for (uint32_t i=0;i<160000;i++) {}
			
			
    // FLAG IS SENT NOW, TIME TO DISPLAY
    UART0_OutBuffer(rb_MCU);
			
        
    // change state to TX state
    current_mode3_option = mode3_fsm[current_mode3_option].next[0];
		ClearBuffer(rb_PC);
    return 1;
}