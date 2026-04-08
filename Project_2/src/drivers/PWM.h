// PWM.h
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Pulse Swift Modulation drivers and HAL to control LED - Hanna Estrada
// Team #: 6
// Team members: Justin Narciso, Natasha Kho, Hanna Estrada

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 

#include <stdint.h>
#include "../config.h"

// System clock is 16MHz. Set total period to 
#define TOTAL_PERIOD 100 			// 16MHz/160000=100
#define PORTF_MASK          0x0E
#define PORTF_UNLOCK        0x4C4F434B
#define PORTF_RECONFIG      0x1F
#define PORTF_PCTL_CLEAR    0x0000FFF0
#define PORTF_PCTL_SET      0x00005550  
#define PWM_ACTIVATION      0x02
#define PWM_DIVIDER         0x00100000
#define PWM_CTL             0x00000002
#define PWM_GENA            0xC8 
#define PWM_GENB            0xC08
#define PWM_CMP_ZERO        0
#define PWM1_COUNTDOWN_CTL  0x00000001
#define PWM1_ENABLE         0x000000E0            


void PWM1_PF123_Init(void);
void ActivateLED(char LED_color, unsigned long brightness_duty);