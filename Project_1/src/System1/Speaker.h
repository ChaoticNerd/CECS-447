// Speaker.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

// Variables for initialization
#define SPEAKER_IN 0x10
#define SPEAKER_CLEAR_PCTL 0x000F0000

#define SPEAKER (*((volatile unsigned long *)0x40024040)) // define SPEAKER connects to PE4

// Function prototype
void Speaker_Init(void);
