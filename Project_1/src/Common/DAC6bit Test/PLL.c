// PLL.c
// Course number:
// Term: 
// Project number: 
// Project description:
// Team #:
// Team members: 
 
#include "PLL.h"

// ~~~~~~~~~~     PLL_Init     ~~~~~~~~~~
// Used to initialize PLL and change clock source. Changes system frequency to 20Mhz.
// Input: none
// Output: none
void PLL_Init(void){
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2; // activate RCC2 PLL usage with advanced features
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2; // set PLL bypass to initialize

  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL value
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;// set XTAL value to 16MHz crystal
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source value
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;// set oscillator source to main oscillator
	
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2; // clear PWRDN to activate PLL
	
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear PLL clock divider
                  + (SYSDIV2);      // set clock divider to 19, (19+1) divides 400MHz by 20
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){}; // wait for PLL to lock
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2; // clear PLL bypass to use PLL
}