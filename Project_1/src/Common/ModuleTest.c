// gpio_btn.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "../tm4c123gh6pm.h"
#include "gpio_btn.h"
#include "../src/System2/DAC.h"

#include "Timer0A.h"
#include "PLL.h"
#include <stdint.h>
#include <stdbool.h>

// preprocessor directives for module name
// Example:
// #define MODULE_1_TEST

#ifdef moduletest
//#define button_test
//#define onboard_button_test
//#define DAC_test
#define timer_test
uint8_t octave_song; 
uint8_t mode; // 0 = piano, 1 = auto-play
uint8_t num_octaves = 3,
		num_songs 	= 3;

bool SW1_pressed = false;

bool C_KEY_PRESSED = false, 
	 D_KEY_PRESSED = false, 
	 F_KEY_PRESSED = false, 
	 E_KEY_PRESSED = false;


#define NUM_VALs  16  // Assume 3-bit DAC is used, that will give 16 values for one period.
#define NUM_NOTEs 8   // number of notes to be played repeatedly

const unsigned long Tone_Tab[] = 
// Note name: C, D, E, F, G, A, B, C'
// Offset:0, 1, 2, 3, 4, 5, 6, 7
{38168*2,34014*2,30303*2,28653*2,25510*2,22727*2,20243*2,19120*2}; // C4 Major notes
//{15289*2,13621*2,12135*2,11454*2,10204*2,9091*2,8099*2,7645*2}; // C5 Major notes
//{7645*2,6810*2,6067*2,5727*2,5102*2,4545,4050*2,3822*2}; // C6 Major notes

// functions prototypes
void System_Init(void);
void BTNS_init(void);
void Button_Test(void);
void Onboard_Button_Test(void);
void Piano_Mode();
void Auto_Mode(); 
void GPIOPortF_Handler(void);
void GPIOPortF_Handler(void);
void DAC_Sound_test();
void Timer0A_test(void);
void Delay10ms(void);
void dummy(void);

void EnableInterrupts(void);
void DisableInterrupts(void);
void WaitForInterrupt(void);

int main(void){
	System_Init();
	
	while(1){

		#ifdef button_test
		Button_Test();
		#endif

		#ifdef onboard_button_test
		Onboard_Button_Test();
		#endif

		#ifdef DAC_test
		DAC_Sound_test();
		#endif

		#ifdef timer_test
		Timer0A_test();
		#endif
		
	}
}

void System_Init(void){
	DisableInterrupts();
	#ifdef button_test
		BTNS_init();
		LED_init();
	#endif

	#ifdef onboard_button_test 
		BTNS_init();
		LED_init();
		mode = 0;
	#endif

	#ifdef DAC_test
		BTNS_init();
		LED_init();
		DAC_Init();
		Timer0A_init();
		DisableInterrupts();    
		
	#endif

	#ifdef timer_test
		PLL_Init();
		Timer0A_init();
		LED_init();
	#endif

	EnableInterrupts();
}


#ifdef button_test 
void Button_Test(void){
	if(C_KEY_PRESSED){
		LED = 0x08;
	}else if(D_KEY_PRESSED){
		LED = 0x02;
	}else if(E_KEY_PRESSED){
		LED = 0x04;
	}else if(F_KEY_PRESSED){
		LED = 0x0A;
	}else{
		LED = 0x00;
	}
}
#endif

#ifdef onboard_button_test 
// Lo/Song 1  	= 0RED 	 / 3PINK
// Mid/song 2	= 1BLUE	 / 4CYAN
// Hi/song 3	= 2GREEN / 5YELLOW
void Onboard_Button_Test(void){
	if (mode == 0){
		if (octave_song == num_octaves){		// if octave_song is 3 in auto mode, reset to 0 when switching to piano mode
			octave_song = 0;
		} else
			octave_song = (octave_song) % num_octaves; // converts octave_song from 4 songs auto mode to 3 octaves piano mode
	} else 
		octave_song = (octave_song) % num_songs; // converts octave_song from 3 songs piano mode to 4 songs auto mode

	if(SW1_pressed){
		if(mode == 0){
			octave_song = (octave_song + 1) % num_octaves;	// increment octave_song  in piano mode, only 3 octaves, increment octave_song
		} else {
			octave_song = (octave_song + 1) % num_songs;	// increment octave_song in auto-play mode, There may be more than 3 songs
		}
		SW1_pressed = false;
	}

	switch(mode){
		case 0:
			Piano_Mode();
			break;
		
		case 1:
			Auto_Mode();
			break;
	}
	
}

void Piano_Mode(void){
	switch(octave_song){//octage_song used to determine which octave we are using
		//Piano Mode:
		case 0: //LOW OCTAVE
			LED = 0x02; // RED
			break;
		case 1: //MID OCTAVE
			LED = 0x04; // BLUE
			break;
		case 2: //HI OCTAVE
			LED = 0x08; // GREEN
			break;
	}
}
	
void Auto_Mode(void){
	switch(octave_song){ //octave_song used to determine which song we are playing
		//Autoplay Mode:
		case 0: //Song 1
			LED = 0x06; // PINK
			break;
		case 1: //Song 2
			LED = 0x0C; // CYAN
			break;
		case 2: //Song 3
			LED = 0x0A; // YELLOW
			break;
//		case 3: //EXTRA CREDIT SONG
//			LED = 0x0E;
//			break;
	}
}
#endif


#ifdef DAC_test
void DAC_Sound_test(){ 
	unsigned char i,j,input,previous; 
	unsigned char tone_index = 0;	
  
	// Automatic play for all 8 notes
	for(i=0;i<8;i++){
		EnableInterrupts();
		Timer0A_Start(Tone_Tab[i]/NUM_VALs);      // Play 8 major notes
		for (j=0;j<50;j++) 
			Delay10ms();  // delay for tempo
		DisableInterrupts();		
	}


	// // Manual play: push SW1 for one note, release and push again moves to the next note.
	// previous = Switch_In()&0x10;
	// while(1){ 
	// 	input = Switch_In()&0x10; // bit 4 means SW1 pressed
	// 	if(input&&(previous==0)){ // just pressed     
	// 	EnableInterrupts();
	// 	Sound_Start(Tone_Tab[tone_index]/NUM_VALs);      // Play 8 major notes
	// 			tone_index = (tone_index+1)%NUM_NOTEs;					// move to the next note
	// 	}
	// 	if(previous&&(input==0)){ // just released     
	// 	DisableInterrupts();    // stop sound
	// 			LED &= ~0x08; // turn off green test LED	
	// 	}
	// 	previous = input; 
	// 	Delay10ms();  // remove switch bounce    
	// }  
}

void Delay10ms(void){unsigned long volatile time;
  time = 18181;  // 10msec
  while(time){
		time--;
  }
}


#endif

// before class tomorrow, or during class, try making the handler just flick the LED on/off without all the fancy callback stuff
#ifdef timer_test
void Timer0A_test(void) {
	static uint32_t test_reload1 =  2000000; // with 20 MHz, this should be 0.001 sec

	// THIS IS TESTING FOR 1 MS
	Timer0A_Change_Reload(test_reload1);
	Timer0A_Start();
	LED = 0x02;
	WaitForInterrupt(); // turns LED off after 1 ms
	WaitForInterrupt(); // wait another 1 ms to show down cycle
	LED = 0x02;			// Turn LED on
	WaitForInterrupt(); // wait another 1 ms; turns LED off
	WaitForInterrupt(); // wait another 1 ms to show down cycle
	Timer0A_Stop(); // 1 ms test complete

	Timer0A_Change_Reload(test_reload1/2); // testing 0.5ms reload changing function
	Timer0A_Start();
	LED = 0x02;
	WaitForInterrupt(); // turns LED off after 0.5 ms
	WaitForInterrupt(); // wait another 0.5 ms to show down cycle
	LED = 0x02;			// Turn LED on
	WaitForInterrupt(); // wait another 0.5 ms; turns LED off
	WaitForInterrupt(); // wait another 0.5 ms to show down cycle
	Timer0A_Stop(); // 0.5 ms test complete
}
#endif


void dummy(void) {}

#ifdef button_test
void GPIOPortE_Handler(void){
	static int yeet;
	// simple solution to take care of button debounce: 20ms to 30ms delay
  for (uint32_t i=0;i<160000;i++) {}
	if(GPIO_PORTE_RIS_R&C_KEY){
		C_KEY_PRESSED = !C_KEY_PRESSED;
		GPIO_PORTE_ICR_R |= C_KEY;


	}else if(GPIO_PORTE_RIS_R&D_KEY){
		GPIO_PORTE_ICR_R |= D_KEY;
		D_KEY_PRESSED = !D_KEY_PRESSED;

	}else if(GPIO_PORTE_RIS_R&F_KEY){
		GPIO_PORTE_ICR_R |= F_KEY;
		F_KEY_PRESSED = !F_KEY_PRESSED;

	}else if(GPIO_PORTE_RIS_R&E_KEY){
		GPIO_PORTE_ICR_R |= E_KEY;
		E_KEY_PRESSED = !E_KEY_PRESSED;
	}

}
#endif

#ifdef onboard_button_test
void GPIOPortF_Handler(void){
	// simple solution to take care of button debounce: 20ms to 30ms delay
  	for (uint32_t i=0;i<160000;i++) {}

	if( GPIO_PORTF_RIS_R&SW1_MASK){
		SW1_pressed = true;
		GPIO_PORTF_ICR_R |= SW1_MASK;
		
	} 
	if( GPIO_PORTF_RIS_R&SW2_MASK){
		LED = 0x00;
		mode ^= 1;
		GPIO_PORTF_ICR_R |= SW2_MASK;
	}
}
#endif

#ifdef timer_test
void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER0_ENABLE;   // acknowledge timer1A timeout
	LED = 0x00;
}
#endif

#endif