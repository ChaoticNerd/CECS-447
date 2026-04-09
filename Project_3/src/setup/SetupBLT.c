// SetupBLT.c
// Runs on TM4C123
// This is an example program to setup HC-05 Bluetooth module with no user interface.
// UART0 is used for the TM4C123 to communicate with PC serial terminal, 
// UART1 is used for the TM4C123 to cummunicate with HC-05 Bluetooth module
// U1Rx (PB0) connects to HC-05 TXD pin
// U1Tx (PB1) connects to HC-05 RXD pin
// HC-05 VCC connects to vbus pin on TM4C123
// HC-05 EN connects to +3.3v
// By Hanna Estrada

#include "../tm4c123gh6pm.h"
#include "UART0.h"
#include "../common/drivers/UART1.h"
#include <stdint.h>  // for data type alias


void clear_buffer(uint8_t *bufPt);
bool userFinished = 0;
extern bool BLT_Finished;
uint8_t BluetoothResponse[30];

// main function for programming BT device with no UI
int main(void) {
	
	uint8_t PCInput[30];
	uint8_t i;
	uint8_t SetCommands[][30] = {"AT+NAME=BeeHive\r\n","AT+UART=57600,0,1\r\n","AT+PSWD=2567\r\n","AT+ROLE=0\r\n"};
	uint8_t QueryCommands[][30] = {"AT+NAME?\r\n","AT+UART?\r\n","AT+PSWD?\r\n","AT+ROLE?\r\n", "AT+VERSION?\r\n"};
  UART0_Init();
	UART1_Init();
  
	uint8_t WelcomeScreen[][30] = {">>> Welcome to Serial ", "Terminal. <<<\r\n",
																 ">>> This is the setup ", "program for HC-05 ", "Bluetooth module. <<<\r\n",
																 ">>> You are at \'AT\'", " Command Mode. <<<\r\n",
																 ">>> Example: AT+", "NAME=Your Name <<<\r\n"
																};
	
	for (int i = 0; i < 9; i++) {
		UART0_OutString(WelcomeScreen[i]); 	
	}
	
  while (1) {
		UART0_InString(PCInput, 30);
		while(!userFinished);
		
		UART1_OutString(PCInput);
		
		UART1_InString(BluetoothResponse);
		UART0_OutString(BluetoothResponse);
		clear_buffer(BluetoothResponse);
		if (!BLT_Finished) {
			UART1_InString(BluetoothResponse);
			UART0_NextLine();	
			UART0_OutString(BluetoothResponse);
		}
		
		clear_buffer(PCInput);
		clear_buffer(BluetoothResponse);
		UART0_NextLine();		
		UART0_NextLine();
		BLT_Finished = false;
		userFinished = false;
	}
}

void clear_buffer(uint8_t *bufPt) {
	for(int i = 0; i < 30; i++) {
		bufPt[i] = 0;
	}
}