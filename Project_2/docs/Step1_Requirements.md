# Step 1 – Requirements & Constraints

## Functional Requirements

- Three different modes
    - MCU_1 is initial master
    - Stays in specific communication mode until exit
    - Select mode from PC_1 terminal
    - MODE SELECT MENU (in order):
        - Welcome to CECS 447 Project 2 – UART
        - MCU1
        - Main Menu
        - 1. PC <--> MCU1 LED Control.
        - 2. MCU1 <--> MCU2 Color Wheel.
        - 3. PC1 <--> MCU1 <--> MCU2 <--> PC2 Chat Room
        - Please choose a communication mode (enter 1 or 2 or 3):
    ---
    - ### MODE 1:
        - MODE 1 NOTES (PRE-SELECT)
            - PC_2 display doesn't change from initial
            - MCU_2 is IDLE
        - Display Menu (PC_1 ONLY):
            - 1. Choose LED Colour
            - 2. Change brightness of LED
            - 3. EXIT
        
        - **OPTION 1**:
            - USER SELECT 1 
            - DISPLAYS:
                - MCU1 Initates communication by sending prompt to PC terminal 1 to select color:
                    - r(red)
                    - b(blue)
                    - g(green)
                    - y(yellow)
                    - c(cyan)
                    - p(purple)
                    - w(white) 
                    - d(dark)
                - Carriage return (\r) to overwrite the line with proper text:
                    - Red LED is on
                    - MODE 1 MENU
            - SOFTWARE RESULT:
                - Change the signal sent to onboard LED to change the color 
            - HARDWARE RESULT:
                - Change the color of the LED on the selected color
            - DISPLAYS: 
                - [LED COLOR] LED is displayed at
                - Return to Mode 1 Menu
        
        - **OPTION 2**:
            - USER SELECT 2
            - DISPLAYS:
                - Please enter a decimal number from 0 to 100 followed by a return:
            - SOFTWARE RESULT:
                - Triggers PWM duty cycle according to decimal number (0% - 100%)
                    - Has to have a baseline where it's not blinking
            - HARDWARE RESULT:
                - Change brightness of LEDs
            - DISPLAYS:
                - [LED COLOR] LED is displayed at [DECIMAL]% brightness
                - Re-display rest of MODE 1 MENU UNDERNEATH new text
        - **OPTION 3**:
            - USER SELECT 3
            - LEAVE MODE 1
                - Display the original MODE SELECT menu
    ---
    - ### MODE 2:
        - MCU_1 STARTS AS MASTER
            - After MCU_1 selects a color, MCU_2 is master
            - Back and Forth from there
        - MCU_1 UART0 RX interrupt 
            - Checks to see if sending a "^"
            - Once detected, exits to MAIN MENU
            
        - DISPLAYS: 
            - Terminal 1 displays the Mode 2 Menu with it prompting '^' for Exit, and a message saying current [color]:
                - Mode 2 MCU1: press ^ to exit this mode
                - In color Wheel State.
                - Please press sw2 to go through the colors in the following color wheel: Dark, Red, Green, Blue, Yellow, Cran, Purple, White.
                - Once a color is selected, press sw1 to send the color to MCU2.
                - Current color: Dark
                - Update color message based on SW2 cycling through colors in round robin order:

            - Terminal 2 displays the waiting message

            - on MCU1, SW2 confirming the selected color

        - HARDWARE RESULT: 
            - MCU1 Cycles through LED color when SW2 is pressed in round robin order:
                - Dark
                - Red
                - Green
                - Blue
                - Yellow
                - Cyan 
                - Purple
                - White
            - MCU 2 is in idle state

            - upon SW1 pressed on MCU1 selects color
                - Selected color is sent to MCU2 
                - MCU1 enters idle state
                - Roles are reveresed, MCU1 is Slave and MCU2 is Master

        - SOFTWARE RESULT:
            - Changes the color of the LED based on the color selected

            - On SW1 press, sends color over to MCU 2
                - SEND CHAR TO MCU2
                - MCU 1 Enters idle waiting for color code from MCU 2
        
    ---
    - ### MODE 3:
        - Maximum 30 characters per message
        - SOFTWARE RESULT:
            - PC1
                - show chatroom instructions
                - MCU1 can send first message
            - PC2
                - show chatroom instructions
        - HARDWARE RESULT:
            - Press SW1 - exits chatroom and return to main menu
        - DISPLAYS:
            - chatroom instructions:
                - PC1
                    - Mode 3 MCU2: Chat Room
                    - Press sw1 at any time to exit the chat room.
                    - Please type a message end with a return (less than 30 characters):
                - PC2
                    - Mode 3 MCU2: Chat Room
                    - Press sw1 at any time to exit the chat room.
                    - Waiting for a message from MCU1 …
                - Both
                    - Shows new user messages on a new line
            

## Constraints
- Three different baudrates
    - Between PC_1 and MCU_1
    - Between MCU_1 and MCU_2
    - Between MCU_2 and PC_2
    - NOT ALLOWED BAURDRATES:
        - 15200
        - 38400
        - 57600
- Two different UART modules
    - MUST use two different UART modules between MCU_1 and MCU_2
    - NOT ALLOWED UARTs:
        - UART 1
        - UART 2
        - UART 3
- INTERRUPTS:
    - UART7 RX for MCU_1 <--> MCU_2
        - For MODE 3 communication between boards
    - MCU_1 UART0 RX for MODE 2
        - EXIT MODE 2
    - SW1 for MODE 2
        - Send LED to other MCU
    - SW2 for MODE 2
        - Round-robin LED colors

## AI Verification Summary
 - Didn't use it this time :rat: