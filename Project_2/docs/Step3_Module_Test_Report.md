# Step 3 – Module Testing Report

## Module-Level Traceability Table

|  Requirement  | Responsible Module | Module Test Evidence | TC ID |
|---------------|-------------------|----------------------|--------|
|Onboard Switches set corresponding pin to high when pressed|Switches.c:Board_BTNS_Init()|evidence/OnBoardButtons_test.mov|TC-MOD-001|
|Onboard Switches trigger corresponding interrupt|Switches.c:Board_BTNS_Init(); Mode2.c:PortF_Interrupt(); Mode3.c:PortF_Interrupt();|evidence/OnBoardButtons_test.mov|TC-MOD-002|
|All onboard LED combinations can be shown|LED.c:LED_Init(); Mode2.c:Mode2_Function()|evidence/LED_test.mov|TC-MOD-003|
|UART0 RX interrupt successfully receives transmission|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(); UART0.c:UART0_Init();|evidence/TransmitUART5_ReceiveUART7.mov, evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-004|
|UART5 RX interrupt successfully receives transmission|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-005|
|UART7 RX interrupt successfully receives transmission|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART5_ReceiveUART7.mov|TC-MOD-006|
|UART0 RX interrupt successfully transmits data|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART5_ReceiveUART7.mov, evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-007|
|UART5 RX interrupt successfully transmits data|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART5_ReceiveUART7.mov|TC-MOD-008|
|UART7 RX interrupt successfully transmits data|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-009|
|Ring Buffer Head stores data successfully|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART5_ReceiveUART7.mov, evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-010|
|Ring Buffer Tail reads data successfully|RingBuffer.c:RingBuffer(), UART0Interrupt_Handler(), UART5Interrupt_Handler(), UART7Interrupt_Handler()|evidence/TransmitUART5_ReceiveUART7.mov, evidence/TransmitUART7_ReceiveUART5.mov|TC-MOD-011|
|PWM displays LED at different brightnesses|PWM.c:PWM1_Init(), ChangeLEDBrightness()|evidence/PWM_Test.mov|TC-MOD-012|
|Main Menu FSM displays all states|mode_manager.c:mode_manager()|evidence/MainMenu_FSM.mov|TC-MOD-013|
|Mode 1 Menu FSM displays all states|mode_manager.c:mode1_menu()|evidence/Mode1_FSM.mov|TC-MOD-014|
|Mode 2 Waiting/Receiving FSM displays all states|mode_manager.c:mode2_menu()|evidence/Mode2_FSM.mov|TC-MOD-015|
|Mode 3 Waiting/Receiving FSM displays all states|mode_manager.c:mode3_menu()|evidence/Mode3_FSM.mov|TC-MOD-016|
|UART0: Press Backspace on PC serial terminal|RingBuffer.c:UART0_Handler()|RingBuffer.c:UART0_Handler()|TC-INT-062|
|Exceeding buffer size|RingBuffer.c:UART0_Handler(), UART5_Handler(), UART7_Handler()|RingBuffer.c:UART0_Handler(), UART5_Handler(), UART7_Handler()|TC-INT-063|
|MainMenu/Mode1: Invalid menu input|mode_manager.c:mode_manager(), mode1_menu()|mode_manager.c:mode_manager(), mode1_menu()|TC-INT-064|
|Mode1: Invalid number input|mode_manager.c:mode1_menu()|mode_manager.c:mode1_menu()|TC-INT-065|
|Mode1: Invalid color input|mode_manager.c:mode1_menu()|mode_manager.c:mode1_menu()|TC-INT-066|




## Module Test Results

### Normal Test Cases

**Switches**  
Owner:  Natasha Kho  
Reviewer:  Justin Narciso, Hanna Estrada  
| TC ID | Expected |  
|-------|----------|
|TC-MOD-001|Onboard SW1 turn LED red, SW2 turn LED blue|
|TC-MOD-002|Onboard SW1 turn LED red, SW2 turn LED blue|


**LED**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho, Justin Narciso  
| TC ID | Expected |  
|-------|----------|
|TC-MOD-003|All onboard LED combinations shown|

**UART0**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho, Justin Narciso   
| TC ID | Expected |  
|-------|----------|
|TC-MOD-004|UART0 RX interrupt successfully receives transmission from PC to MCU|
|TC-MOD-007|UART0 RX interrupt successfully transmits data from MCU to PC|

**UART5**  
Owner: Justin Narciso  
Reviewer: Natasha Kho, Hanna Estrada  
| TC ID | Expected |  
|-------|----------|
|TC-MOD-005|UART5 RX interrupt successfully receives transmission from MCU1 to MCU2|
|TC-MOD-008|UART5 RX interrupt successfully transmits data from PC1 to PC2|

**UART7**  
Owner: Natasha Kho  
Reviewer: Justin Narciso, Hanna Estrada  
| TC ID | Expected |  
|-------|----------|
|TC-MOD-006|UART7 RX interrupt successfully receives transmission from MCU2 to MCU1|
|TC-MOD-009|UART7 RX interrupt successfully transmits data from PC2 to PC1|

**Ringbuffer**  
Owner: Justin Narciso    
Reviewer: Natasha Kho, Hanna Estrada   
| TC ID | Expected |  
|-------|----------|
|TC-MOD-010|Ring Buffer Head stores data successfully and is then read to be outputted on PC|
|TC-MOD-011|Ring Buffer Tail reads data successfully and outputs data to PC|

**PWM**  
Owner: Hanna Estrada   
Reviewer: Natasha Kho  
| TC ID | Expected |  
|-------|----------|
|TC-MOD-012|PWM displays LED at different brightnesses |

**FSM**  
Owner: Justin Narciso   
Reviewer: Hanna Estrada, Natasha Kho   
| TC ID | Expected |  
|-------|----------|
|TC-MOD-013|Main Menu FSM displays all states; main = white, mode1 = red, mode2 = blue, mode3 = green, and beyond scope defaults to white.|
|TC-MOD-014|Mode 1 Menu FSM displays all states; mode1_menu = white, option1 = red, option2 = blue, option 3 = green* out of scope = white. *Since option 3 = is exit it resets before leaving and green doesn't display|
|TC-MOD-015|Mode 2 Waiting/Receiving FSM displays all states; MCU1 to MCU2 = red, MCU2 to MCU1 = blue, upon exit sets to red|
|TC-MOD-016|Mode 3 Waiting/Receiving FSM displays all states; MCU1 to MCU2 = red, MCU2 to MCU1 = blue, upon exit sets to red|


### Edge Case Tests

**UART0**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho, Justin Narciso   
| TC ID | Expected |  
|-------|----------|
|TC-INT-062|UART0: Press Backspace on PC serial terminal; fills buffer but performs backspace operation on outputted terminal|

**Ringbuffer**  
Owner: Justin Narciso   
Reviewer: Natasha Kho, Hanna Estrada  
| TC ID | Expected |  
|-------|----------|
|TC-INT-063|Input exceeding buffer size; overwrites prev data with new data |

**FSM**  
Owner: Justin Narciso  
Reviewer: Hanna Estrada, Natasha Kho  
| TC ID | Expected |  
|-------|----------|
|TC-INT-064|MainMenu/Mode1: Invalid menu input; default to|
|TC-INT-065|Mode1: Invalid number input; default to white|
|TC-INT-066|Mode1: Invalid color input; default to prev color|

## Results Overview
**Switches**  
Owner:  Natasha Kho  
Reviewer:  Justin Narciso, Hanna Estrada  
Acceptance: Switches operate as intended with no issues that can be found.

**LED**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho, Justin Narciso   
Acceptance: LED display all colors possible on the onboard LEDs and with the use of PWM is able to alter the brightness.


**UART0**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho, Justin Narciso    
Acceptance: Is fully operational and fully capable of receiving and transmiting data between MCU and PC. However the issue with backspace filling a buffer can be remedied.  

**UART5**  
Owner: Justin Narciso   
Reviewer: Natasha Kho, Hanna Estrada  
Acceptance: Is fully operational without any issue handling the MCU1 to MCU2 communicatiosn effectively and is sucessfully receiving and transmitting data.   

**UART7**  
Owner: Natasha Kho  
Reviewer: Justin Narciso, Hanna Estrada   
Acceptance: Is fully operational without any issue handling the MCU2 to MCU1 communicatiosn effectively is sucessfully receiving and transmitting data.  

**Ringbuffer**  
Owner: Justin Narciso   
Reviewer: Natasha Kho, Hanna Estrada  
Acceptance: Ringbuffer is at the correct buffer size of 30 characters for successful operation. Head increment when the uart handlers receive data, and tail increments when the buffer is accessed or read from. There is the edge case in which data exceeds the buffer size, in which case head loops back to the beginning and overwrites earlier parts of the received data in order to retain speed.   


**PWM**  
Owner: Hanna Estrada  
Reviewer: Natasha Kho  
Acceptance: PWM operates perfectly as intended with its use in LED being able to change the birghtness of the LED, by changing how the duration of LED is on or off, being perceived as changing brightness.   


**FSM**  
Owner: Justin Narciso  
Reviewer: Hanna Estrada, Natasha Kho  
Acceptance: All FSMs operate as intended with exit conditions and is properly able to the egecases such exceeding the scope. In which the input is invalid it results in a default where it returns to the base case of the FSM instead of trying to call on an operation that doesn't exist.   
