// main_p2.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

#include "../tm4c123gh6pm.h"
#include "../Common/gpio_btn.h"
#include "../src/System2/DAC.h"
#include "../Common/Timer0A.h"
#include "../Common/PLL.h"
#include <stdint.h>
#include <stdbool.h>

struct Note {
  uint8_t tone_index;
  uint8_t delay;
};
typedef const struct Note NTyp;

#define PAUSE 67				// assume there are less than 255 tones used in any song

#define C4 	0
#define C4S 1
#define D4 	2
#define D4S 3
#define E4 	4
#define F4 	5
#define F4S 6
#define G4 	7
#define G4S 8
#define A4 	9
#define A4S 10
#define B4 	11
#define C5 	(0 + 1*12)
#define C5S (1 + 1*12)
#define D5 	(2 + 1*12)
#define D5S (3	+ 1*12)
#define E5 	(4	+ 1*12)
#define F5 	(5	+ 1*12)
#define F5S (6	+ 1*12)
#define G5 	(7	+ 1*12)
#define G5S (8	+ 1*12)
#define A5 	(9	+ 1*12)
#define A5S (10 + 1*12)
#define B5 	(11 + 1*12)
#define C6 	(0	+ 2*12)
#define C6S (1	+ 2*12)
#define D6 	(2	+ 2*12)
#define D6S (3	+ 2*12)
#define E6 	(4	+ 2*12)
#define F6 	(5	+ 2*12)
#define F6S (6	+ 2*12)
#define G6 	(7	+ 2*12)
#define G6S (8	+ 2*12)
#define A6 	(9	+ 2*12)
#define A6S (10 + 2*12)
#define B6 	(11 + 2*12)
#define C7 	(0	+ 3*12)
#define C7S (1	+ 3*12)

uint8_t octave_select = 0,
				song_select = 0;
uint8_t mode; // 0 = piano, 1 = auto-play
uint8_t num_octaves = 3,
		num_songs 	= 4;

bool SW1_pressed = false;

bool C_KEY_PRESSED = false, 
	 D_KEY_PRESSED = false, 
	 F_KEY_PRESSED = false, 
	 E_KEY_PRESSED = false;

#define NUM_VALS  64 
#define NUM_NOTES 12   //number of notes per octave	

unsigned char Index;

const unsigned long Tone_Tab[] = 
// Note name: C, CS, D, DS, E, F, FS, G, GS, A, AS, B,
// Offset:		0, 1,	 2, 3,	4, 5, 6, 	7,  8, 9, 10,	11,
//C 0		,CS 1		 ,D 2 	 ,DS 3 	 ,E	4		 ,F	5		,FS 6 	,G 7		,GS 8	  ,A 9		,AS 10	,B 11
{38168*2,36101*2,34014*2,32154*2,30395*2,28653*2,27027*2,25510*2,24096*2,22727*2,21459*2,20243*2,	 	// C4 notes
19120*2, 18051*2,17036*2,16077*2,15175*2,14327*2,13514*2,12755*2,12034*2,11364*2,10730*2,10121*2,	  // C5 notes
9560*2,		9025*2,	8518*2,	8039*2,	7587*2,	7163*2,	6761*2,	6382*2,	6024*2,	5682*2,	5365*2,	5063*2, 	// C6 notes
4780*2, 4513*2}; // C7, C7S


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
 C5,4,A4,4,F4,4,E4,4,D4,8,B4,2,B4,2,A4,4,F4,4,G4,4,F4,12},

//score table for Memory - Toby Fox
{E4,4,B4,4,A4,4,E4,4,G4S,6,G4S,6,A4,8,E4,4,A4,4,E4,4,G4S,6,G4S,6,A4,4,
 E4,4,B4,4,A4,4,E4,4,G4S,6,G4S,6,A4,8,E4,4,A4,4,C5S,4,B4 ,6,A4 ,5,B4,5,0,0}
};

const unsigned char SineWave[64] = {32,35,38,41,44,47,50,52,55,57,58,60,61,62,63,63,
																		63,63,63,62,61,59,58,56,53,51,48,46,43,40,37,34,
																		30,27,24,21,18,16,13,11, 8, 6, 5, 3, 2, 1, 1, 1,
																		 1, 1, 2, 3, 4, 6, 7, 9,12,14,17,20,23,26,29,32};

// function prototypes
void System_Init(void);
void Piano_Mode(void);
void Auto_Mode(NTyp music_score[]);
void Delay(void);

void EnableInterrupts(void);
void DisableInterrupts(void);
void WaitForInterrupt(void);

void System_Init(void);

int main(void){	
  System_Init();
  //Timer0A_Change_Reload( Tone_Tab[ C4 + ( NUM_NOTES * (octave_select%num_octaves) )] / NUM_VALS); //to select a fequency for reload set call tone_tab[ C4 + ( 7 * selected octave)]
  //Timer0A_Start();	//start time for the frequecy
	
  while(1){
		
		if(SW1_pressed){
			if (mode == 0)
				octave_select++;// = (octave_select + 1) % num_octaves; // cycles through 0-2 octaves in piano mode
			else
				song_select++;// = (song_select + 1) % num_songs; // cycles through 0-3 songs in auto mode
			SW1_pressed = false;
		}
		
		switch(mode){
			case 0: //Piano Mode on case 0 
				Piano_Mode();
				break;
			case 1: //Auto Mode on case 1 
				Timer0A_Stop();
				Auto_Mode(mysong[song_select%num_songs]);
				break;
		}	
  }
}

void System_Init(void){
	DisableInterrupts();
	PLL_Init();
	Timer0A_Init();
	DAC_Init();
	BTNS_Init();
	EnableInterrupts();
}

void Piano_Mode(void){
	
	Timer0A_Stop();
	if(C_KEY_PRESSED){	// if C Key pressed 
		Timer0A_Change_Reload( Tone_Tab[ C4 + ( NUM_NOTES * (octave_select%num_octaves) )] / NUM_VALS); //to select a frequency for reload set call tone_tab[ C4 + ( 7 * selected octave)]
		Timer0A_Start();
		while(C_KEY_PRESSED);
	}else if(D_KEY_PRESSED){
		Timer0A_Change_Reload(Tone_Tab[ D4 + (NUM_NOTES * (octave_select%num_octaves) )] / NUM_VALS); //to select a frequency for reload set call tone_tab[ D4 + ( 7 * selected octave)]
		Timer0A_Start();
		while(D_KEY_PRESSED);
	}else if(E_KEY_PRESSED){
		Timer0A_Change_Reload(Tone_Tab[ E4 + ( NUM_NOTES * (octave_select%num_octaves) )] / NUM_VALS); //to select a frequency for reload set call tone_tab[ E4 + ( 7 * selected octave)]
		Timer0A_Start();
		while(E_KEY_PRESSED);
	}else if(F_KEY_PRESSED){
		Timer0A_Change_Reload(Tone_Tab[ F4 + (NUM_NOTES * (octave_select%num_octaves) )] / NUM_VALS); //to select a frequency for reload set call tone_tab[ F4 + ( 7 * selected octave)]		
		Timer0A_Start();
		while(F_KEY_PRESSED);
	}
	
	Timer0A_Stop();

	
}

void Auto_Mode(NTyp music_score[]){
	uint8_t i=0, j;
	
	while(music_score[i].delay) {
		if(SW1_pressed || !mode){
			Timer0A_Stop();
			break;
		}
		if (music_score[i].tone_index==PAUSE) // index = 255 indicate a pause: stop systick
			Timer0A_Stop(); // silence tone, turn off timer
		else {
			Timer0A_Change_Reload(Tone_Tab[music_score[i].tone_index + ( NUM_NOTES * (octave_select%num_octaves))]/NUM_VALS); //set to reload to change DAC
			Timer0A_Start();	//start time
		}
		for (j = 0; j < music_score[i].delay*10; j++){ //delay till sound fully played
			Delay();
			if (SW1_pressed || !mode) { // check if SW1 was pressed (change song)
				Timer0A_Stop();
				break;	// end while loop to start new song
			}
		}

		Timer0A_Stop(); // stop tone after delay
		i++;
		if(music_score[i].tone_index == music_score[i - 1].tone_index)
			Delay();

	}

	for (j = 0; j < music_score[i].delay*10; j++) // delays sound until next repeat
			Delay();
}

void GPIOPortE_Handler(void){
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

void GPIOPortF_Handler(void){
	// simple solution to take care of button debounce: 20ms to 30ms delay
  	for (uint32_t i=0;i<160000;i++) {}

	if( GPIO_PORTF_RIS_R&SW1_MASK){
		SW1_pressed = true;						//boolean var to be used to signal to change octave or song
		GPIO_PORTF_ICR_R |= SW1_MASK;
	} 

	if( GPIO_PORTF_RIS_R&SW2_MASK){
		mode ^= 1;										//Invert mode between 0 for Piano mode and 1 Auto mode
		GPIO_PORTF_ICR_R |= SW2_MASK;	
	}
}

void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;   // acknowledge timer1A timeout
  	Index = (Index+1)&0x3F;        // 16 samples for each period
	DAC = SineWave[Index]; // output to DAC: 6-bit data
}

void Delay(void){
	uint32_t volatile time;
  time = 18181;  // 0.001sec
  while(time){
		time--;
  }
}
