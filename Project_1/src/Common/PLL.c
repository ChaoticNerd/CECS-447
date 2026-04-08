// PLL.c
// Course number: CECS 447
// Term: Spring 2026
// Project number: 1
// Project description: Make an embedded audio system. Four external buttons play piano note C/D/E/F. There's also auto-play mode.
//                      On board buttons SW1 and SW2 switch between auto-play and piano.
// Team #: 6
// Team members: Hanna Estrada, Justin Narciso, Natasha Kho 
 
#include "PLL.h"

// ~~~~~~~~~~     PLL_Init     ~~~~~~~~~~
// Used to initialize PLL and change clock source. Changes system frequency to 20Mhz.
// Input: none
// Output: none
void PLL_Init(void){
	// default 400MHz
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
	
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
	
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// configure for main oscillator source
	
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
	
  // 4) set the desired system divider and the system divider least significant bit
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~SYSCTL_RCC2_R_CLEAR_CLKDIV) // clear system clock divider field
                  + (SYSDIV);      // configure for 20 MHz clock
	
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
		
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}