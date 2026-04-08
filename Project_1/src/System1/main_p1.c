// main_p1.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho

#include "../tm4c123gh6pm.h"
#include "../Common/gpio_btn.h"
#include "../Common/PLL.h"
#include "../Common/Timer0A.h"
#include "../System1/Speaker.h"

#include <stdint.h>
#include <stdbool.h>

// number definitions
#define num_octaves 	3
#define num_songs			4
#define software_10ms	181810
#define num_notes			12
#define piano_mode 		0
#define autoplay_mode 1

// global variables
uint8_t mode; 				// determines piano vs autoplay mode
											// 0 = piano, 1 = auto-play
uint8_t octave = 0, 	// determines the octave when % 3
											// 0 = lower, 1 = middle, 2 = higher
				song 	= 0; 		// determines the song when % 4
											// 0 = , 1 = , 2 = , 3 = 
										
bool 	SW1_pressed = false;			// what is this for lol

bool 	C_KEY_PRESSED = false, 		// determines whether to play C note
			D_KEY_PRESSED = false, 		// determines whether to play D note
			F_KEY_PRESSED = false, 		// determines whether to play F note
			E_KEY_PRESSED = false;		// determines whether to play E note
			

// Music / Song Definitions			
#define C4    	0
#define C4S 		1
#define D4      2
#define D4S 		3
#define E4      4
#define F4      5
#define F4S 		6
#define G4      7
#define G4S 		8
#define A4      9
#define A4S 	  10
#define B4      11
#define C5      (0 	 + 1*12)
#define C5S 		(1 	 + 1*12)
#define D5      (2 	 + 1*12)
#define D5S 		(3    + 1*12)
#define E5      (4    + 1*12)
#define F5      (5    + 1*12)
#define F5S 		(6    + 1*12)
#define G5      (7    + 1*12)
#define G5S 		(8    + 1*12)
#define A5      (9    + 1*12)
#define A5S 		(10 	 + 1*12)
#define B5      (11	 + 1*12)
#define C6      (0    + 2*12)
#define C6S 		(1    + 2*12)
#define D6      (2    + 2*12)
#define D6S 		(3    + 2*12)
#define E6      (4    + 2*12)
#define F6      (5    + 2*12)
#define F6S 		(6    + 2*12)
#define G6      (7    + 2*12)
#define G6S 		(8    + 2*12)
#define A6      (9    + 2*12)
#define A6S 		(10	 + 2*12)
#define B6      (11	 + 2*12)
#define C7      (0    + 3*12)
#define C7S			(1    + 3*12)


const unsigned long Tone_Tab[] = 
// Note name: C, CS, D, DS, E, F, FS, G, GS, A, AS, B,
// Offset:        0, 1,     2, 3,    4, 5, 6,     7,  8, 9, 10,    11,
//C 0        ,CS 1         ,D 2      ,DS 3      ,E    4         ,F    5        ,FS 6     ,G 7        ,GS 8      ,A 9        ,AS 10    ,B 11
{38168*2,36101*2,34014*2,32154*2,30395*2,28653*2,27027*2,25510*2,24096*2,22727*2,21459*2,20243*2,         // C4 notes
19120*2, 18051*2,17036*2,16077*2,15175*2,14327*2,13514*2,12755*2,12034*2,11364*2,10730*2,10121*2,      // C5 notes
9560*2,        9025*2,    8518*2,    8039*2,    7587*2,    7163*2,    6761*2,    6382*2,    6024*2,    5682*2,    5365*2,    5063*2,     // C6 notes
4780*2, 4513*2}; //C7, C7S

			
 #define PAUSE 255				// assume there are less than 255 tones used in any song

// define music data structure 
struct Note {
  uint8_t tone_index;
  uint8_t delay;
};
typedef const struct Note NTyp;

// doe ray mi fa so la ti 
// C   D   E  F  G  A  B
NTyp mysong[][255] = {
 
// score table for Mary Had A Little Lamb
{E4, 4, D4, 4, C4, 4, D4, 4, E4, 4, E4, 4, E4, 8, 
 D4, 4, D4, 4, D4, 8, E4, 4, G4, 4, G4, 8,
 E4, 4, D4, 4, C4, 4, D4, 4, E4, 4, E4, 4, E4, 8, 
 D4, 4, D4, 4, E4, 4, D4, 4, C4, 8, 0, 0 },

// score table for Twinkle Twinkle Little Stars
{C4,4,C4,4,G4,4,G4,4,A4,4,A4,4,G4,8,F4,4,F4,4,E4,4,E4,4,D4,4,D4,4,C4,8, 
 G4,4,G4,4,F4,4,F4,4,E4,4,E4,4,D4,8,G4,4,G4,4,F4,4,F4,4,E4,4,E4,4,D4,8, 
 C4,4,C4,4,G4,4,G4,4,A4,4,A4,4,G4,8,F4,4,F4,4,E4,4,E4,4,D4,4,D4,4,C4,8,0,0},
	
// score table for Happy Birthday version 2, lower pitch
{C4,2,C4,2,D4,4,C4,4,F4,4,E4,8,C4,2,C4,2,D4,4,C4,4,G4,4,F4,8,C4,2,C4,2,
 C5,4,A4,4,F4,4,E4,4,D4,8,B4,2,B4,2,A4,4,F4,4,G4,4,F4,12, 0, 0},

//score table for Memory - Toby Fox
{E4,4,B4,4,A4,4,E4,4,G4S,6,G4S,6,A4,8,E4,4,A4,4,E4,4,G4S,6,G4S,6,A4,4,
 E4,4,B4,4,A4,4,E4,4,G4S,6,G4S,6,A4,8,E4,4,A4,4,C5S,4,B4 ,6,A4 ,5,B4,5,0,0}
};


// function prototypes
void System_Init(void);
void Piano_Mode(void);
void Autoplay_Song(NTyp scoretab[]);
void Delay10ms(void);
void EnableInterrupts(void);
void DisableInterrupts(void);
void WaitForInterrupt(void);
	
int main(void){	
  System_Init();
	
  while(1){
		//playNotes();
		switch(mode) {
			case 0: // mode selected is piano mode
				if(SW1_pressed) { // check if switch 1 is pressed
					octave++;				// in piano mode ==> update octave
					SW1_pressed = false; // turn off SW1
				}
				Piano_Mode(); // play piano function
				WaitForInterrupt(); // wait for key to be pressed/unpressed
				break;	// exit case
			case 1: // mode selected is song mode
				if(SW1_pressed) { // check if switch 2 is pressed
					song++;					// in autoplay mode ==> update song
					SW1_pressed = false; // turn off SW1
				}
				Autoplay_Song(mysong[song % num_songs]); // automatically play selected song
				break; // exit case
		}
  }
}

// ~~~~~~~~~~     System_Init     ~~~~~~~~~~
// Calls all system initialize functions, such as PLL, Buttons, Timer0A, etc.
// Input: none
// Output: none
void System_Init(void) {
	// Initialize all necessary Functions
	DisableInterrupts();
	PLL_Init();
	LED_init();
	BTNS_Init();
	Speaker_Init();
	Timer0A_Init();
	EnableInterrupts();
}

// ~~~~~~~~~~     Delay10ms     ~~~~~~~~~~
// A software busy wait. Used to calculate note duration for autoplay mode.
// Input: none
// Output: none
void Delay10ms(void){
	unsigned long volatile time; // create variable time
  time = software_10ms;  // set time to approximately 10msec
  while(time){
		time--; // count down time in while loop to count 10msec
  }
}

// ~~~~~~~~~~     Piano_Mode     ~~~~~~~~~~
// Controls the Piano Mode for the main loop. Checks which button (piano key) is being pressed and sets
// the Timer0A frequency accordingly to play the note.
// Input: none
// Output: none
void Piano_Mode(void) {
	Timer0A_Stop();	// stop Timer for reload
	if(C_KEY_PRESSED){	// if C Key pressed 
		Timer0A_Change_Reload(Tone_Tab[C4+(num_notes*(octave%num_octaves))]); //to select a frequency for reload set call tone_tab[ C4 + ( 12 * selected octave)]
		Timer0A_Start();	// start Timer0A to play note
		while(C_KEY_PRESSED);	// keep playing music while c key is still pressed
	}else if(D_KEY_PRESSED){	// if D Key pressed
		Timer0A_Change_Reload(Tone_Tab[D4+(num_notes*(octave%num_octaves))]); //to select a frequency for reload set call tone_tab[ D4 + ( 12 * selected octave)]
		Timer0A_Start();	// start Timer0A to play note
		while(D_KEY_PRESSED);	// keep playing music while d key is still pressed
	}else if(E_KEY_PRESSED){	// if E Key pressed
		Timer0A_Change_Reload(Tone_Tab[E4+(num_notes*(octave%num_octaves))]); //to select a frequency for reload set call tone_tab[ E4 + ( 12 * selected octave)]
		Timer0A_Start();	// start Timer0A to play note
		while(E_KEY_PRESSED);	// keep playing music while e key is still pressed
	}else if(F_KEY_PRESSED){	// if F Key pressed
		Timer0A_Change_Reload(Tone_Tab[F4+(num_notes*(octave%num_octaves))]); //to select a frequency for reload set call tone_tab[ F4 + ( 12 * selected octave)]		
		Timer0A_Start();	// start Timer0A to play note
		while(F_KEY_PRESSED);	// keep playing music while f key is still pressed
	}
	Timer0A_Stop();	// stop Timer0A to stop note playing
}

// ~~~~~~~~~~     Autoplay_Song     ~~~~~~~~~~
// Controls the Autoplay Song Mode for the main loop. Checks which song is set and loops through all notes in the
// song array to play a song on loop until either the mode is changed or the song is changed.
// Input: NTyp scoretab[]
// Output: none
void Autoplay_Song(NTyp song_array[])
{
	uint8_t i=0, j; // create variables i, j for looping song/delay

	while (song_array[i].delay) { // while there is a valid note delay
		if (SW1_pressed || (mode == 0)) { // check if SW1 was pressed (change song)
			break;	// end while loop to start new song
		}
		
		if (song_array[i].tone_index==PAUSE) // index = 255 indicate a pause: stop Timer0A
			Timer0A_Stop(); // pause Timer0A to prevent sound from playing
		else {
			// otherwise, set Timer0A reload value to desired note frequency
			Timer0A_Change_Reload(Tone_Tab[song_array[i].tone_index + (num_notes*(octave%num_octaves))]);
			// start Timer0A, interrupts will handle music playing
			Timer0A_Start();
		}

		// play the software delay based on note length. interrupt will play during busy waits
		for (j=0;j<song_array[i].delay;j++) {
			Delay10ms();
			if (SW1_pressed || (mode == 0)) { // check if SW1 was pressed (change song)
				break;	// end while loop to start new song
			}
		}
		
		// stop Timer0A when note ends to stop music
		Timer0A_Stop();
		//if (song_array[i].tone_index == song_array[i-1].tone_index)
			//Delay10ms();
		i++;  // play the next note
	}
	
	// short delay after each song
	for (j=0;j<10;j++) 
		Delay10ms();
}

// ~~~~~~~~~~     GPIOPortE_Handler     ~~~~~~~~~~
// Handles Port E Interrupts. Tracks which buttons, or piano key, was pressed.
// Input: none
// Output: none
void GPIOPortE_Handler(void){
	// simple solution to take care of button debounce: 20ms to 30ms delay
  for (uint32_t i=0;i<160000;i++) {}
		
	// if E0 (C Key) was pressed, set C_KEY_PRESSED variable
	if(GPIO_PORTE_RIS_R&C_KEY){
		C_KEY_PRESSED = !C_KEY_PRESSED;
		GPIO_PORTE_ICR_R |= C_KEY;

	// if E1 (D Key) was pressed, set D_KEY_PRESSED variable
	}else if(GPIO_PORTE_RIS_R&D_KEY){
		GPIO_PORTE_ICR_R |= D_KEY;
		D_KEY_PRESSED = !D_KEY_PRESSED;

	// if E2 (F Key) was pressed, set F_KEY_PRESSED variable	
	}else if(GPIO_PORTE_RIS_R&F_KEY){
		GPIO_PORTE_ICR_R |= F_KEY;
		F_KEY_PRESSED = !F_KEY_PRESSED;

	// if E3 (E Key) was pressed, set E_KEY_PRESSED variable
	}else if(GPIO_PORTE_RIS_R&E_KEY){
		GPIO_PORTE_ICR_R |= E_KEY;
		E_KEY_PRESSED = !E_KEY_PRESSED;
	}

}

// ~~~~~~~~~~     GPIOPortF_Handler     ~~~~~~~~~~
// Handles Port F Interrupts. Tracks which onboard switch was pressed. Changes between piano and autoplay modes if SW2.
// Input: none
// Output: none
void GPIOPortF_Handler(void){
	// simple solution to take care of button debounce: 20ms to 30ms delay
  for (uint32_t i=0;i<160000;i++) {}

	// if F0 was pressed, set SW1_pressed variable to true
	if( GPIO_PORTF_RIS_R&SW1_MASK){
		SW1_pressed = true;
		GPIO_PORTF_ICR_R |= SW1_MASK;
	} 
	
	// if F4 was pressed, invert mode (switch between piano and autoplay)
	if( GPIO_PORTF_RIS_R&SW2_MASK){
		mode ^= 1;
		GPIO_PORTF_ICR_R |= SW2_MASK;
	}
}

// ~~~~~~~~~~     Timer0A_Handler     ~~~~~~~~~~
// Handles Timer0A Interrupts. Inverts speaker bit to turn on and off to desired note frequency.
// Input: none
// Output: none
void Timer0A_Handler(void){
	SPEAKER ^= SPEAKER_IN;	// invert speaker bit to turn it on and off
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;   // acknowledge timer0A timeout

}
