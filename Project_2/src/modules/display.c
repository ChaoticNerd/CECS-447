
// display.c
// Course number: 447
// Term: Spring 2026
// Project number: 2
// Driver description: Handles displaying menu for each MCU
// Team #: 6
// Team members: Natasha Kho, Hanna Estrada, Justin Narciso


// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files. 
#include "display.h"

extern void UART0_OutString(char str[]);
extern char *brightness_str[3];

// Ouputs Main Menu on MCU 1 through UART0
void displayMainMenu_MCU1(void) {
    char str[]= 
        "\n\rWelcome to CECS 447 Project 2 UART\n\n"
        "\rMCU1\n\n"
        "\rMain Menu\n"
        "\r\t1. PC<->MCU1 LED Control.\n"
        "\r\t2. MCU1<->MCU2 Color Wheel.\n"
        "\r\t3. PC1<->MCU1<->MCU2<->PC2 Chat.\n\n"
        "\rPlease choose communication Mode:\n"
        "\r(Enter 1, 2, 3): \0";

    UART0_OutString(str);
}

// Ouputs Main Menu on MCU 2 through UART0
void displayMainMenu_MCU2(void) {
    char str[] = 
        "\n\n\rWelcome to CECS 447 Project 2 - UART\n"
        "\rMCU 2\n"
        "\rWaiting for command from MCU1...\n\0";

    UART0_OutString(str);
}

// Ouputs Mode 1 Menu on MCU 1 through UART0
void displayModeOneMenu_MCU1(void){
    char str[] =
    "\n\n\rMode 1 Menu"
    "\n\rPlease select an option from the following list (enter 1 or 2 or 3):"
    "\n\r\t1. Choose an LED color."
    "\n\r\t2. Change the brightness of current LED(s)."
    "\n\r\t3. Exit.\n\r\0";
    UART0_OutString(str);
}

// Ouputs Mode One Menu on MCU 2 through UART0
void displayModeOneMenu_MCU2(void){
    displayMainMenu_MCU2();
}

// Ouputs Mode 2 First Menu Type on MCU 1 through UART0
void displayModeTwoMenu_MCU1_Initial(void){
    char *color = getColor();

    char str[] = 
    "\n\n\rMode 2 MCU1: press ^ to exit this mode"
    "\n\rIn color Wheel State."
    "\n\rPlease press sw2 to go through the colors in"
    "\n\rthe following color wheel: Dark, Red, Green,"
    "\n\rBlue, Yellow, Cran, Purple, White."
    "\n\rOnce a color is selected, press sw1 to send"
    "\n\rthe color to MCU2."
    "\n\rCurrent color: ";
    char strOut[sizeof(str) + sizeof(color) + 2];
	sprintf(strOut, "%s%s%s", str, color, "\0");
    UART0_OutString(strOut);
}

// Ouputs Mode 2 First Menu Type on MCU 2 through UART0
void displayModeTwoMenu_MCU2_Initial(void){
    char str[] =
    "\n\n\rMode 2 MCU2"
    "\n\rWaiting for color code from MCU1 ...\0";
    UART0_OutString(str);
}

// Ouputs Mode 2 Second Menu Type on MCU 1 through UART0
void displayModeTwo_MCU1_Cont(void){
    char *color = getColor();

    char str[] = 
    "\n\n\rMode 2 MCU1: press ^ to exit"
    "\n\rCurrent color: ";
	char str2[] = "\n\rWaiting for color code from MCU2 ...";
    char strOut[sizeof(str) + sizeof(str2) + sizeof(color) + 2];
	sprintf(strOut, "%s%s%s%s", str, color, str2, "\0");
    
    UART0_OutString(strOut);
}

// Ouputs Mode 2 Second Menu Type on MCU 2 through UART0
void displayModeTwo_MCU2_Cont(void){
    
    char str[] = 
    "\n\n\rMode 2 MCU2"
    "\n\rIn color Wheel State."
    "\n\rPlease press sw2 to go through the colors"
    "\n\rin the following color wheel: Dark, Red,"
    "\n\rGreen, Blue, Yellow, Cran, Purple, White."
    "\n\rOnce a color is selected, press sw1 to"
    "\n\rsend the color to MCU1.";

    char strOut[sizeof(str) + 1];
	sprintf(strOut, "%s%s", str, "\0");
    UART0_OutString(strOut);
}

// Ouputs Mode 3 Menu on MCU 1 through UART0
void displayModeThreeMenu_MCU1(void){
    char str[] =
    "\n\n\rMode 3 MCU1: Chat Room"
    "\n\rPress sw1 at any time to exit the chat room."
    "\n\rPlease type a message end with a return"
    "\n\r(less than 30 characters):\n\r\0";
    UART0_OutString(str);
}

// Ouputs Mode 3 Menu on MCU 2 through UART0
void displayModeThreeMenu_MCU2(void){
    char str[] =
    "\n\n\rMode 3 MCU2: Chat Room"
    "\n\rPress sw1 at any time to exit the chat room."
    "\n\rWaiting for a message from MCU1...\0";
    UART0_OutString(str);
}


// Outputs text for Mode 1 Option 1 through UART0
void displayLEDSelect(void){
    char str[] = 
        "\n\n\rPlease select a color from the following list:"
        "\n\r\td(dark), r(red), g(green), b(blue), y(yellow), c(cyan), p(purple), w(white)): \0";

    UART0_OutString(str);

}

// Outputs text for Mode 1 Option 2 through UART0
void displayBrightnessSelect(void){
	char str[] = "\n\n\rPlease enter a decimal number from 0 to 100 followed by a return: \0";

    UART0_OutString(str);
}

void displayCurrentColor(void){
    for (uint32_t i=0;i<160000;i++) {}
	char *color = getColor();
	char str[] = 
		"\n\rCurrent color: ";
	char strOut[sizeof(str) + sizeof(*color) + 2];
	sprintf(strOut, "%s%s%s", str, color, "\0");
	UART0_OutString(strOut);
}

// asks tasha?
void displayLEDBrightness(uint8_t brightness) {
			char *color = getColor();
		
			char str[] = 
      " LED is displayed at ";
			
			char str2[] =
			" brightness.\0";
			
			char strOut[3 + sizeof(str) + sizeof(str2) + sizeof(color) + 2];
			
			sprintf(strOut, "%s%s%s%d%s", "\n\r", color, str, (brightness + '0' - '0'), str2);
			UART0_OutString(strOut);
}

// Outputs when invalid input from any mode/menu
void displayTryAgainInput(void){
    char str[] = 
    "\n\r Invalid Input. Try again!\0";
    UART0_OutString(str);
}

// A function to get the color of the current LED
// For: Mode 2, Mode 1
char* getColor(void){
    switch(get_current_color()){
        case 'r':    
					return "RED";
        case 'b':   
					return "BLUE";
        case 'g':  
					return "GREEN";
        case 'y': 
					return "YELLOW";
        case 'c':   
					return "CYAN";
        case 'p': 
					return "PURPLE";
        case 'w':  
					return "WHITE";
        case 'd':    
					return "OFF";
        default:     
					return "UNKNOWN";
    }
}