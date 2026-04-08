// gpio_btn.h
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 

// Variable definition
#define LED         (*((volatile unsigned long *) 0x40025038))  // use onboard three LEDs: PF321
#define PIANO_KEYS  (*((volatile unsigned long *) 0x4002403C)) // External buttons on PE0123
#define BOARD_BTNS  (*((volatile unsigned long *) 0x40025040)) // On-board buttons on PF0 (SW2), PF4 (SW1)

// Masks to use for main
#define SW1_MASK 0x01				// PF0
#define SW2_MASK 0x10				// PF4
#define C_KEY       0x01    // PE0
#define D_KEY       0x02    // PE1
#define F_KEY       0x08    // PE3
#define E_KEY       0x04    // PE2

// Initialization definitions (Port F04, Port E0-3)
#define BOARD_BTNS_IN 0x11	
#define EXTERNAL_BTNS_IN 0x0F
#define UNLOCK_PORTF0 0x4C4F434B
#define BOARD_BTNS_CLEAR_PCTL    0x000F000F 
#define EXTERNAL_BTNS_CLEAR_PCTL 0x0000FFFF
#define BOARD_BTNS_PUR 0x11 // 0 to set to default low
#define EXTERNAL_BTNS_PUR 0x00
#define PORTF_IRQ 0x40000000 
#define PORTE_IRQ 0x00000010

// Function prototypes
void LED_init(void);
void BTNS_Init(void);
void Piano_keys_init(void);
void Board_BTNS_init(void);
