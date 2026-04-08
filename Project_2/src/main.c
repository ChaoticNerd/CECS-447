// main.c
// Course number: 447
// Term: 6
// Project number: 2 
// Project description: The communication between two MCUs and PCs through the use of UART, 
// and changing the function of the program based on which inputs are read from PC terminal or MCU.
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso

// function prototypes
void System_Init(void);

#include "drivers/Switches.h"
#include "drivers/UART7.h"
#include "drivers/UART5.h"
#include "drivers/UART0.h"
#include "drivers/PWM.h"
#include "modules/ring_buffer.h"
#include "modules/mode_manager.h"
#include "modules/display.h"
#include "config.h"
#include <stdbool.h>

extern uint8_t user_inputString[BUFFER_SIZE];
extern RingBuffer *rb_MCU;
extern RingBuffer *rb_PC;
extern bool userFinished;
extern bool invalid;
int invalid_char = 255;

extern void EnableInterrupts();
extern void DisableInterrupts();


int main(void){	
  System_Init();

  // PROGRAM START:
	#ifdef MCU_1
	displayMainMenu_MCU1();
	#endif
	
	#ifdef MCU_2
	displayMainMenu_MCU2();
	#endif
  while(1){
		
    if(userFinished){ // runs other code only if user has finished
      #ifdef MCU_1
			
			reset_arrayInt();
				for (int i = 0; i < BUFFER_SIZE; i++) {
					user_inputString[i] = (uint8_t) UART_ReadChar(rb_PC);
					if ((i > MIN_VALID_CHAR) && (user_inputString[i] != invalid_char))
						invalid = INVALID_TRUE;
				}

				if (invalid) {
						userFinished = false;
						invalid = INVALID_FALSE;
						displayMainMenu_MCU1();
				}
			else {
        userFinished = false;
        int curr_mode = mode_manager_MCU1((char) user_inputString[0]); // enters mode
			}
      #endif
    }
		#ifdef MCU_2
				char waitFlag = UART_ReadChar(rb_MCU);
				while( (waitFlag != (char) ANGRY) && (waitFlag != (char) FLAG) && (waitFlag != (char) BETA) ){
					waitFlag = UART_ReadChar(rb_MCU);
				}
				mode_manager_MCU2(waitFlag);
				displayMainMenu_MCU2();
      #endif
  }
}

void System_Init(void) {
	DisableInterrupts();
  Board_BTNS_Init();

  PWM1_PF123_Init();
	
	#ifdef MCU_1
  UART5_Init();
	#endif
	
  UART0_Init();
	
	#ifdef MCU_2
  UART7_Init();
	#endif

  rb_init(rb_MCU);	
  rb_init(rb_PC);	
	EnableInterrupts();
}


