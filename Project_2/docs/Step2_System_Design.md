# Step 2 – System Design & Module Planning

## Design Option A

### Hardware Plan

##### UART7 - MCU_1 --> MCU_2
    - PE0 (RX)
    - PE1 (TX)
##### UART5 - MCU_2 --> MCU_1
    - PE4 (RX)
    - PE5 (TX)
##### LEDs
    - PF1-3
##### SW
    - PF0 (SW1)
    - PF4 (SW2)
---
### Software Feature Implementation Method
For board to board communications MCU1 utilizes UART5 and MCU2 utilizes UART7, and both MCUs communicate to their respective PC terminals via UART0. The UART5 and UART7 will have be set to RX interrupt for immediate response and non-blocking operation. 
Next the LED is controlled via the M0PWM6 on PD0 and will be connected to the onboard-LED. The PWM will change the frequeny in which the onboard-LEDs turn on and off to change brightness.
The system will also use PF0 and PF1 or the onboard SW1 and SWW2 to perform certain functions. In mode 2 SW1 will be used to confirm a color selection, and SW2 will be used to cycle through the colors.
Within main it contains all three mode logic in the system, and contains all the handlers such as the PortF for the on board buttons, PortD for the PWM, PortE for UART5, and PortC handlers for UART7.

## Design Option B

### Hardware Plan
##### UART4 - MCU_1 --> MCU_2
    - PC4 (RX)
    - PC5 (TX)
##### UART7 - MCU_2 --> MCU_1
    - PE0 (RX)
    - PE1 (TX)
##### LEDs
    - PF1-3
##### SW
    - PF0 (SW1)
    - PF4 (SW2)
---
### Software Feature Implementation Method
For board to board communications MCU1 utilizes UART5 and MCU2 utilizes UART7, and both MCUs communicate to their respective PC terminals via UART0. The UART5 and UART7 will have be set to RX busy waits systems to ensure that all data is transferred.
Next the LED is controlled via the M0PWM6 on PD0 and will be connected to the onboard-LED. The PWM will change the frequeny in which the onboard-LEDs turn on and off to change brightness.
The system will also use PF0 and PF1 or the onboard SW1 and SWW2 to perform certain functions. In mode 2 SW1 will be used to confirm a color selection, and SW2 will be used to cycle through the colors.
Within main it contains all three mode logic in the system, and contains all the handlers such as the PortD for the PWM, and PortF the on board buttons.

## Selected Design
After looking at the pros and cons of both designs, we decided to use Design A. Design A uses interrupts for receiving transmissions, which helps decrease the delay between transmitting and receiving. Without interrupts, as seen in Design B, the receiver has to wait a specific amount of time before checking if any data has been received, increasing the delay between receiving and transmitting. This is significant especially in the chatroom, where the users expect near-instant messaging. With the delay, users will notice that their messages are not sending as fast as they expecting it to, leading to user dissatisfaction with the program. Ultimately, we want the best user satisfaction with the program, so reducing the delays by adding interrupts for UART receiver will fit this project best.

## Module Design & Assignment Table

| Module Name | Responsibility | Assigned Team Member |
|-------------|---------------|----------------------|
|      main.c             |       Main loop logic       |           Justin           |
|      main.c             |       Mode 1 Function, LED changer       |           Hanna           |
|      main.c             |       Mode 2 Function, MCU round-robin LED       |           Natasha           |
|      main.c             |       Mode 3 Function, chatroom       |           Justin           |
|      main.c             |       Interrupt logic       |           Natasha           |
|      UART.c             |       Initializes UART0,5,7 on PE0,1,4,5 with interrupt       |           Hanna           |
|      UART.c             |       Contains UART serial terminal functions       |           Natasha           |
|      PWM.c              |       Initializes PWM on PD0 with interrupt, contains PWM functions        |           Hanna           |
|      LED_Switch.c       |       Initializes PF0-4 to activate onboard switches with interrupt and LEDs        |           Justin           |
