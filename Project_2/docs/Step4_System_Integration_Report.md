# Step 4 – System Integration & Verification

## Integration Order

We did individual parts first. Hanna created the functions for PWM and the LED. Natasha handled UART. Justin handled the FSMs. Then, we integrated them in order of the menu. We started by creating the functions for Mode 1 to work. Hanna Integrated PWM with Mode 1 options while Justin got the FSM working. Natasha worked on the communication from Board 1 to Board 2 and for the FSM to work. 
We then integrated Mode 2. We worked together on this one, though most of the code was supplied by Hanna's PWM and LED drivers and HAL.
Lastly, we integrated Mode 3. We worked together on this one, though most of the code was present from the Module Test. By this time, we all had a better understanding of FSMs and UART, so it was faster.

## Final Call Graph
 ![Final Call Graph](/evidence/Step4_Robustness/Callgraph.png "Final Call Graph")

## Final Data Flow Diagram
 ![Final Data Flow Diagram](/evidence/Step4_Robustness/Dataflow.png "[Final Data Flow Diagram")

## System-Level Traceability Table

| Requirement | System Test Method | Evidence | Pass/Fail |
|-------------|--------------------|----------|-----------|
| Display Main Menu on PC Terminal 1 (PC1) | Power on system and verify main menu text appears on PC1 serial terminal | `evidence/SYS-15_MainStart.png` | Pass |
| Display Waiting Screen on PC Terminal 2 (PC2) | Power on system and verify waiting screen appears on PC2 serial terminal | `evidence/SYS-15_MainStart.png` | Pass |
| System stays in selected communication mode until it exits | Enter any mode and verify system remains until exit command or switch event | `evidence/SYS-19_Mode1Exit.mov`, `evidence/SYS-10_Mode2Exit.mov`, `evidence/SYS-13_Mode3MCU1Exit.mov`, `evidence/SYS-14_Mode3MCU2Exit.mov` | Pass |
| Use UART RX interrupt to read user input from Main Menu (1,2,3) | Enter menu options via PC1 terminal and verify correct mode is selected | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Input '1' and hit enter on PC1 in Main Menu to enter Mode 1 | Send `1` from PC1 terminal and confirm Mode 1 activates | `evidence/SYS-16_Mode1Enter.mov` | Pass |
| Mode 1: PC2 only displays waiting screen | Enter Mode 1 and verify PC2 remains on waiting screen | `evidence/SYS-16_Mode1Enter.mov` | Pass |
| Mode 1: PC1 shows Mode 1 Menu | Enter Mode 1 and confirm Mode 1 menu appears on PC1 | `evidence/SYS-16_Mode1Enter.mov` | Pass |
| Mode 1: Use UART RX interrupt to read user input from Mode 1 Menu (1,2,3) | Enter menu selections in Mode 1 and verify proper action occurs | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 1: Input '1' and hit enter on PC1 to select 'Change LED color' option | Send `1` in Mode 1 menu and verify LED color option executes | `evidence/SYS-17_Mode1ChangeColor.mov` | Pass |
| Mode 1: Display user prompt to input a color to PC1 to change LED color | Confirm prompt for color input appears on PC1 | `evidence/SYS-17_Mode1ChangeColor.mov` | Pass |
| Mode 1: Use UART RX interrupt to read user input (d,r,g,b,y,c,m,w) | Send valid color characters and confirm system reads input correctly | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 1: Display on PC1 line 1 the active LED color | Select color and verify color text is displayed on PC1 | `evidence/SYS-17_Mode1ChangeColor.mov` | Pass |
| Mode 1: MCU1 LED displays user LED selection | Observe onboard LED changes to selected color | `evidence/SYS-17_Mode1ChangeColor.mov` | Pass |
| Mode 1: Displays Mode 1 Menu again after completing Option 1 | After color change verify Mode 1 menu reappears | `evidence/SYS-17_Mode1ChangeColor.mov` | Pass |
| Mode 1: Input 2 and hit enter on PC1 to select 'Change LED brightness' option | Send `2` from Mode 1 menu and confirm brightness option activates | `evidence/SYS-18_Mode1ChangeBrightness.mov` | Pass |
| Mode 1: Display user prompt to input number from 0 to 100 on PC1 | Verify brightness input prompt appears | `evidence/SYS-18_Mode1ChangeBrightness.mov` | Pass |
| Mode 1: Use UART RX interrupt to read user input (0-100) | Send brightness values and confirm they are received correctly | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 1: Use PWM duty cycle to set LED brightness based on user input | Enter multiple brightness values and verify LED intensity changes | `evidence/SYS-18_Mode1ChangeBrightness.mov` | Pass |
| Mode 1: Display on PC1 line 1 the current LED brightness | Confirm brightness value is printed on PC1 | `evidence/SYS-18_Mode1ChangeBrightness.mov`| Pass |
| Mode 1: Displays Mode 1 Menu again after completing Option 2 | After brightness change verify menu returns | `evidence/SYS-18_Mode1ChangeBrightness.mov` | Pass |
| Mode 1: Enter '3' and hit enter on PC1 to exit Mode 1 Menu | Send `3` and verify system exits Mode 1 | `evidence/SYS-19_Mode1Exit.mov` | Pass |
| Mode 1: Displays Main Menu on PC1 after exiting Mode 1 | Verify Main Menu appears on PC1 | `evidence/SYS-19_Mode1Exit.mov` |  Pass|
| Enter '2' and hit enter on PC1 in Main Menu to enter Mode 2 | Send `2` from main menu and verify Mode 2 starts | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: MCU1 starts in transmit mode | Observe PC1 display indicating transmit mode | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: MCU2 starts in waiting mode | Observe PC2 display indicating waiting mode | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: PC1 always displays MCU number + exit instructions | Verify PC1 shows MCU ID and exit instructions continuously | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: PC2 always displays MCU number | Verify PC2 shows MCU ID continuously | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: PC1 begins by displaying color wheel instructions | Confirm instructions appear on PC1 at start of Mode 2 | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: PC2 begins by displaying wait screen | Confirm PC2 shows waiting screen | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: PC1 begins by displaying current color | Verify current LED color displayed on PC1 | `evidence/SYS-05_Mode2Enter.mov` | Pass |
| Mode 2: Use Port F interrupt on SW1 and SW2 | Press SW1 and SW2 and confirm interrupts trigger expected behavior | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 2: SW2 changes LED on transmission MCU | Press SW2 and observe LED color change | `evidence/SYS-08_Mode2SendColor.mov` | Pass |
| Mode 2: SW2 updates PC1 display current color | Press SW2 and verify PC1 updates color display | `evidence/SYS-07_Mode2ColorWheel.mov `| Pass |
| Mode 2: SW2 updates transmission MCU LED to match current color | Confirm LED matches new color | `evidence/SYS-07_Mode2ColorWheel.mov` | Pass |
| Mode 2: SW1 on transmission MCU sends color to waiting MCU | Press SW1 and confirm color transmitted | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: Use UART RX interrupt on waiting MCU to receive color | Verify receiving MCU updates LED after transmission | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 2: Waiting MCU LED color updates to received color | Observe LED color update on receiving MCU | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: SW1 changes transmission MCU to waiting MCU | Press SW1 and verify role switch | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: SW1 changes waiting MCU to transmission MCU | Verify other MCU becomes transmitter | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: Updates waiting MCU PC display to show waiting screen and current color | Verify updated display on PC terminal | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: Updates transmission MCU PC display to show color wheel instructions and current color | Verify updated display on PC terminal | `evidence/SYS-08_Mode2SendColor.mov`, `evidence/SYS-09_Mode2BackAndForth.mov` | Pass |
| Mode 2: Input '^' and hit enter on PC1 to exit mode at any time | Send `^` and confirm mode exits | `evidence/SYS-10_Mode2Exit.mov` | Pass |
| Mode 2: Use UART0 RX Interrupt to capture mode termination | Send exit character and verify interrupt triggers exit |` evidence/Dataflow.png`,` evidence/Callgraph.png` | Pass |
| Mode 2: Both MCU LEDs turn off when mode is terminated | Observe LEDs turn off after exit | `evidence/SYS-10_Mode2Exit.mov` | Pass |
| Mode 2: Display Main Menu on PC1 after mode termination | Verify Main Menu appears on PC1 | `evidence/SYS-10_Mode2Exit.mov` | Pass |
| Mode 2: Display Waiting Screen on PC2 after mode termination | Verify waiting screen appears on PC2 | `evidence/SYS-10_Mode2Exit.mov` | Pass |
| Enter '3' and hit enter on PC1 in Main Menu to enter Mode 3 | Send `3` and verify Mode 3 begins | `evidence/SYS-11_Mode3Enter.mov`| Pass |
| Mode 3: MCU1 begins in sending mode | Verify PC1 indicates sending mode | `evidence/SYS-11_Mode3Enter.mov` | Pass |
| Mode 3: MCU2 begins in receiving mode | Verify PC2 indicates receiving mode | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: PC1 displays MCU number, Chat Room title, and exit instructions at all times | Confirm information shown on PC1 | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: PC2 displays MCU number, Chat Room title, and exit instructions at all times | Confirm information shown on PC2 | `evidence/SYS-11_Mode3Enter.mov` | Pass |
| Mode 3: PC1 prompts user to type a message and hit enter to send | Verify message prompt appears | `evidence/ROB-02_Mode3LargeMsg.mov` | Pass |
| Mode 3: Message must have less than 30 characters | Send messages under and over limit and verify validation | `evidence/Dataflow.png`,`evidence/Callgraph.png` | Pass |
| Mode 3: Use UART RX interrupt on receiving MCU to read sent message | Send message and confirm interrupt reception | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: After sending message, update receiving MCU PC to display the sent message on a new line | Verify message appears on receiving terminal | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: After sending message, sending MCU becomes receiving MCU | Verify role switch after message transmission | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: After sending message, receiving MCU becomes sending MCU | Verify role swap | `evidence/SYS-12_Mode3Chatting.mov` | Pass |
| Mode 3: Both PC terminals display full message history | Send multiple messages and confirm history shown | `evidence/Dataflow.png`, `evidence/Callgraph.png` | Pass |
| Mode 3: Use Port F interrupt on SW1 | Press SW1 and confirm interrupt triggers | `evidence/SYS-13_Mode3MCU1Exit.mov`, `evidence/SYS-14_Mode3MCU2Exit.mov` | Pass |
| Mode 3: Press SW1 on either MCU to end mode | Press SW1 and verify Mode 3 exits | `evidence/SYS-13_Mode3MCU1Exit.mov`, `evidence/SYS-14_Mode3MCU2Exit.mov` | Pass |
| Mode 3: Display Main Menu on PC1 after Mode 3 termination | Verify PC1 shows Main Menu | `evidence/SYS-13_Mode3MCU1Exit.mov`, `evidence/SYS-14_Mode3MCU2Exit.mov` | Pass |
| Mode 3: Display Waiting Screen on PC2 after Mode 3 termination | Verify PC2 shows waiting screen | `evidence/SYS-13_Mode3MCU1Exit.mov`, `evidence/SYS-14_Mode3MCU2Exit.mov` | Pass |
| Onboard Switches set corresponding pin to high when pressed | Press switches and verify GPIO input state changes | `evidence/OnBoardButtons_test.mov` | Pass |
| Onboard Switches trigger corresponding interrupt | Verify ISR executes when switch pressed | `evidence/OnBoardButtons_test.mov`| Pass |
| All onboard LED combinations can be shown | Cycle through all colors and confirm correct output | `evidence/LED_test.mov` | Pass |
| UART0 RX interrupt successfully receives transmission | Send UART data and verify reception via UART0 | `evidence/TransmitUART5_ReceiveUART7.mov`, `evidence/TransmitUART7_ReceiveUART5.mov`| Pass |
| UART5 RX interrupt successfully receives transmission | Send UART data and verify reception via UART5 | `evidence/TransmitUART7_ReceiveUART5.mov`| Pass |
| UART7 RX interrupt successfully receives transmission | Send UART data and verify reception via UART7 | `evidence/TransmitUART5_ReceiveUART7.mov` | Pass |
| UART0 RX interrupt successfully transmits data | Send data and verify correct transmission on UART0 | `evidence/TransmitUART5_ReceiveUART7.mov`, `evidence/TransmitUART7_ReceiveUART5.mov` | Pass |
| UART5 RX interrupt successfully transmits data | Send data and verify correct transmission on UART5 | `evidence/TransmitUART5_ReceiveUART7.mov` | Pass |
| UART7 RX interrupt successfully transmits data | Send data and verify correct transmission on UART7 | `evidence/TransmitUART7_ReceiveUART5.mov` | Pass |
| Ring Buffer Head stores data successfully | Insert characters into buffer and verify head index increments | `evidence/TransmitUART5_ReceiveUART7.mov`, `evidence/TransmitUART7_ReceiveUART5.mov` | Pass |
| Ring Buffer Tail reads data successfully | Read characters and verify tail index increments | `evidence/TransmitUART5_ReceiveUART7.mov`, `evidence/TransmitUART7_ReceiveUART5.mov` | Pass |
| PWM displays LED at different brightnesses | Test multiple PWM duty cycles and observe brightness | `evidence/PWM_Test.mov` | Pass |
| Main Menu FSM displays all states | Navigate through menu states and verify transitions | `evidence/MainMenu_FSM.mov` | Pass |
| Mode 1 Menu FSM displays all states | Execute all Mode 1 menu options | `evidence/SYS-01_Mode1Showcase.mov` | Pass |
| Mode 2 Waiting/Receiving FSM displays all states | Trigger role transitions and verify FSM behavior | `evidence/Mode3_FSM.mov` | Pass |
| Mode 3 Waiting/Receiving FSM displays all states | Send messages and verify FSM transitions | `evidence/Mode1_FSM.mov`, `evience/Mode1_MenuSelect.mov` | Pass |
| Mode 1 Functionality Complete | Execute all Mode 1 features successfully | evidence/SYS-01_Mode1Showcase.mov | Pass |
| Mode 2 Functionality Complete | Execute all Mode 2 features successfully | `evidence/Mode2_FSM.mov` | Pass |
| Mode 3 Functionality Complete | Execute all Mode 3 features successfully | evidence/SYS-03_Mode3Showcase.mov | Pass |
| All Modes Complete | Verify system successfully runs all modes sequentially | `evidence/SYS-02_Mode2Showcase.mov` | Pass |
| UART0: Press Backspace on PC serial terminal | Press backspace and verify character deletion handled | `evidence/SYS-03_Mode3Showcase.mov` | Pass |
| Exceeding buffer size | Send input exceeding buffer length and verify proper handling | `evidence/ROB-02_Mode3LargeMsg.mov` | Pass |
| MainMenu/Mode1: Invalid menu input | Enter invalid menu option and verify error handling | `evidence/Mode1_InvalidInput_ExitMenu.mov` | Pass |
| Mode1: Invalid number input | Enter out-of-range brightness value and verify validation | `evidence/SYS-23_Mode1InvalidMenu.mov` | Pass |
| Mode1: Invalid color input | Enter invalid color character and verify error message | `evidence/ROB-01_Mode1InvalidColor.mov` | Pass |


## CER Lite

1. 

    Claim - Users can change the color and brightness of LED in mode 1
    Evidence - `evidence/PWM_Test.mov`
    Reasoning - Option 1 changes the color of the LED. Option 2 changes the brightness of it using PWM1 on PF1, PF2, and PF3

2. 

    Claim - Two users can pass around an LED light between the two boards using the on-board switches
    Evidence - `evidence/Mode2_FSM.mov`
    Reasoning - SW1 changes the color of the LED in a round robin system of: Dark, Red, Green, Blue, Yellow, Cyan, Purple, and White. Pressing SW2 sends the LED color to the other MCU. It also sends a flag to alert the other MCU that it has recieved data. 

3. 
    
    Claim - Users can use Mode 3 to communicate with each other. They take turns sending messages into the chat. There's a 30 character limit.
    Evidence - `evidence/Mode3_FSM.mov`
    Reasoning - Using a two-state Finite State Machine, the MCUs know which state they're in - Transmitting or Receiving. Depending on their state, they send a different flag to the other MCU, which is how they know which state they're in.

4. 

    Claim - Users can choose which mode they want to enter and leave all of them in different ways.
    Evidence - `evidence/MainMenu_FSM.mov`
    Reasoning - From the main menu, they select 1,2, or 3. To leave Mode 1, they enter a 3. To leave Mode 2, the terminal linked to MCU1 sends a '^'. The third state is left using the onboard SW1.


## Robustness Test Description

Mode 1 - Option 2 (Selecting brightness)
    - If the user inputs a number that's outside of the range of 1-100, then it doesn't change the LED brightness.

Mode 3
    - Putting in more than 30 characters will cut the rest of the text.

Mode 1 - Option 1 (Selecting LED color)
    - Putting in several characters will not be registered. The color stays the same - even if it's off to begin with.

## AI Verification Summary
We didn't use AI.