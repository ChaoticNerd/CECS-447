// ModuleTest.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Module description: 
// A brief summary on modules tested in this module test file,
// including module list, responsibility and team member assignment
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso


// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
// Example:
// #include module1_driver.h

#include "drivers/Switches.h"
#include "drivers/UART7.h"
#include "drivers/UART5.h"
#include "drivers/UART0.h"
#include "modules/ring_buffer.h"
#include "modules/mode_manager.h"

// preprocessor directives for module name
// Example:
// #define MODULE_1_TEST

#include <stdint.h>
#include "tm4c123gh6pm.h" // think of where the ModuleTest file is located. We find the location of these headers based on ModuleTest location.

// functions prototypes
void System_Init(void);
void Delay500ms(void);


//#define LED_test
//#define Switch_test
//#define PWM_test
//#define UART5_test
#define UART7_test
//#define UART0_test
//#define UART7_transmit_test
//#define UART5_receive_test
//#define mode_manager_test
//#define mode1_menu_test
//#define mode2_menu_test
//#define mode3_menu_test
//#define ring_buffer_test
//#define UART0_string_test

extern void EnableInterrupts();
extern void WaitForInterrupt();
extern void DisableInterrupts();

#ifdef Switch_test
  uint16_t switch1_test = 0;
  uint16_t switch2_test = 0;
	uint8_t current_color;
#endif

#ifdef LED_test
	uint8_t current_color;
#endif

#ifdef UART5_test
	extern RingBuffer *rb_MCU;
	extern RingBuffer *rb_PC;
	extern bool userFinished;
	//char currentChar5;
#endif

#ifdef UART7_test
	extern RingBuffer *rb_MCU;
	extern RingBuffer *rb_PC;
	char currentChar7;
#endif

#ifdef UART7_transmit_test
	extern RingBuffer *rb_MCU;
	extern RingBuffer *rb_PC;
	extern bool userFinished;
#endif

#ifdef UART5_receive_test
	extern RingBuffer *rb_MCU;
	extern RingBuffer *rb_PC;
	char currentChar5;
#endif

#ifdef mode_manager_test
	extern RingBuffer *rb_PC;
	extern bool userFinished;
	static char input;
#endif

#ifdef mode1_menu_test
	extern RingBuffer *rb_PC;
	extern bool userFinished;
	static char input;
#endif
#ifdef mode2_menu_test
	extern RingBuffer *rb_PC;
	extern bool userFinished;
	static char input;
	extern bool SW1_check;
#endif
#ifdef mode3_menu_test
	int state = 0;
	int mode = 0;
#endif

#ifdef UART0_string_test
	char string[15] = "wowmanywords...";
#endif
// Module test function prototypes
#if defined(MODULE_1_TEST)
void Module_1_Test(void);
#endif


int main(void){
  System_Init();
	
	#ifdef UART5_test	
	UART5_OutCRLF();
	#endif
	
  while(1){
    // Call individual module test functions here
    // Example:
    #if defined(MODULE_1_TEST)
    Module_1_Test();
    #endif

    #ifdef LED_test
      // loop through all LED colors
			set_LED_color('r');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('b');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('g');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('y');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('c');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('p');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('w');
			current_color = get_LED_color();
			Delay500ms();

			set_LED_color('d');
			current_color = get_LED_color();
			Delay500ms();
			Delay500ms();
      
    #endif

    #ifdef Switch_test
      // nothing?? just logic analyzer
    #endif 
	
    #ifdef PWM_test
      Change_LED_Brightness(1000,9000);
			Delay500ms();
			Change_LED_Brightness(9000,1000);
			Delay500ms
    #endif
		
		#ifdef UART5_test
//			sprintf((char *)str, "KOI");
//			UART5_OutString(str);
//			UART5_OutChar('K');
//			UART5_OutChar('O');
//			UART5_OutChar('I');
			
				
			// 0x0A CR?
			if(userFinished) {
				UART0_OutString(rb_PC);
				userFinished = 0;
			}
			
			
//      Delay500ms();
//      currentChar5 = UART5_ReadChar(rb);
//      Delay500ms();
//      currentChar5 = UART5_ReadChar(rb);
//      Delay500ms();
//      currentChar5 = UART5_ReadChar(rb);
//      Delay500ms();

		#endif
		
		#ifdef UART7_test

      Delay500ms();
      currentChar7 = UART_ReadChar(rb_MCU);
			if(currentChar7 != -1)
				UART0_OutChar(currentChar7);
      Delay500ms();
			
		#endif
		
		#ifdef UART7_transmit_test
//			UART7_OutChar('K');
//			UART7_OutChar('O');
//			UART7_OutChar('I');
			if(userFinished) {
				char tempVar = UART_ReadChar(rb_PC);
				while(tempVar != -1){
					UART7_OutChar(tempVar);
					tempVar = UART_ReadChar(rb_PC);
				}
				UART7_OutChar(tempVar);
				userFinished = 0;
			}
		#endif
		
		#ifdef UART5_receive_test
            
      Delay500ms();
      currentChar5 = UART_ReadChar(rb_MCU);
			if(currentChar5 != -1)
			UART0_OutChar(currentChar5);
      Delay500ms();
		#endif
		
		#ifdef UART0_test
		
		#endif
			
		#ifdef mode_manager_test
		if(userFinished){
				char temp = UART_ReadChar(rb_PC);
				userFinished = 0;
				while((temp == -1)|(temp == 0x0A)|(temp == 0x0D)){
					temp = UART_ReadChar(rb_PC);
				}
				input = temp;

		}
		mode_manager(input);
			switch(get_current_mode()){
        case 0: // main menu
            // call main menu
						set_LED_color('w');
            break;
        case 1: // mode 1 menu
						set_LED_color('r');
            break;
        case 2: // mode 2 menu
						set_LED_color('b');
            break;
        case 3: // mode 3 menu
						set_LED_color('g');
            break;
			}
		Delay500ms();
		#endif
		
		#ifdef mode1_menu_test
			if(userFinished){
				char temp = UART_ReadChar(rb_PC);
				userFinished = 0;
				while((temp == -1)|(temp == 0x0A)|(temp == 0x0D)){
					temp = UART_ReadChar(rb_PC);
				}
				input = temp;

		}
		mode1_menu(input);
			switch(get_current_mode1_option()){
        case 0: // main menu
            // call main menu
						set_LED_color('w');
            break;
        case 1: // mode 1 menu
						set_LED_color('r');
            break;
        case 2: // mode 2 menu
						set_LED_color('b');
            break;
        case 3: // mode 3 menu
						set_LED_color('g');
            break;
		}
		Delay500ms();
		#endif
			
		#ifdef mode2_menu_test
			if(userFinished){
				char temp = UART_ReadChar(rb_PC);
				userFinished = 0;
				while((temp == -1)|(temp == 0x0A)|(temp == 0x0D)){
					temp = UART_ReadChar(rb_PC);
				}
				input = temp;

		}
		mode2_menu(input);
			switch(get_current_mode1_option()){
        case 0: // MCU1 to MCU2
						set_LED_color('r');
            break;
        case 1: // MCU2 to MCU1
						set_LED_color('b');
            break;
			}
		Delay500ms();
		#endif

		#ifdef mode3_menu_test
//		if(get_current_mode3_option() == 0){
      	if(userFinished){
        char temp = UART_ReadChar(rb_PC);
            userFinished = 0;
            while((temp == -1)|(temp == 0x0A)){
              temp = UART_ReadChar(rb_PC);
            }
            input = temp;
      }
		
		mode3_menu(input, SW1_pressed);
			switch(get_current_mode3_option()){
				case 0: // MCU1 to MCU2
						set_LED_color('g');
						break;
				case 1: // MCU2 to MCU1
						set_LED_color('r');
						break;
			}
			
		Delay500ms();
		#endif
		#ifdef UART0_string_test
			//UART0_OutString();
		#endif

		
  }
}

void System_Init(void){
  // Example:
  
  DisableInterrupts();
  #if defined(MODULE_1_TEST)
  Module_1_Init();
  #endif	

  #ifdef LED_test
    LED_Init();
  #endif

  #ifdef Switch_test
    Board_BTNS_Init();
			LED_Init();
  #endif

  #ifdef PWM_test
    PWM1_PF123_Init();
  #endif

  #ifdef UART5_test
    UART5_Init();
		rb_init(rb_MCU);	
		rb_init(rb_PC);	
  #endif

  #ifdef UART7_test
    UART7_Init();
		UART0_Init();
		rb_init(rb_MCU);	
		rb_init(rb_PC);	
  #endif
	
	#ifdef UART7_transmit_test
		UART7_Init();
		UART0_Init();
		rb_init(rb_MCU);
		rb_init(rb_PC);
	#endif
	
	#ifdef UART5_receive_test
		UART7_Init();
		UART0_Init();
		rb_init(rb_MCU);	
		rb_init(rb_PC);	
	#endif
		
	 
	#ifdef UART0_test
    UART0_Init(); 
  	#endif

	#ifdef mode_manager_test
		UART0_Init(); 
		LED_Init();
		rb_init(rb_PC);	
	#endif
	
	#ifdef mode1_menu_test
		UART0_Init(); 
		LED_Init();
		rb_init(rb_PC);	
	#endif
		
	#ifdef mode2_menu_test
		UART0_Init(); 
		Board_BTNS_Init();
		LED_Init();
		rb_init(rb_PC);	
	#endif
	
	#ifdef mode3_menu_test
		UART0_Init(); 
		Board_BTNS_Init();
		LED_Init();
		rb_init(rb_PC);	
	#endif
	
	#ifdef UART0_string_test
		UART0_Init(); 
	#endif

  EnableInterrupts();
}

// Module test function definitions
#if defined(MODULE_1_TEST)
void Module_1_Test(void){
}
#endif

// software delay
void Delay500ms(void){
	unsigned long volatile time;
  time = 14545*50;  // 10msec (*50 to get .5 sec)
  while(time){
		time--;
  }
}

#ifdef Switch_test

#endif

#ifdef mode2_menu_test
		void GPIOPortF_Handler(void){
    // simple solution to take care of button debounce: 20ms to 30ms delay
    for (uint32_t i=0;i<160000;i++) {}

    // if F0 was pressed, set SW1_pressed variable to true
    if( GPIO_PORTF_RIS_R&SW1_MASK){
			SW1_check |= true;
			set_LED_color('r');
      GPIO_PORTF_ICR_R |= SW1_MASK;
    } 
    
    // if F4 was pressed, invert mode (switch between piano and autoplay)
    if( GPIO_PORTF_RIS_R&SW2_MASK){
			set_LED_color('b');
      GPIO_PORTF_ICR_R |= SW2_MASK;
    }
  }
#endif