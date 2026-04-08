# Step 3 – Module Test Plan + ModuleTest.c

# Step 3 – Module-by-Module Test Plan
## Project
CECS 447 – Project 1: Digital Piano

## Purpose
This document defines the independent test plan for each software and hardware module in the Digital Piano project.
Each module is tested in isolation using ModuleTest.c prior to full system integration.
---

## Module Overview
| **Module Name** | **Description** |
|------------   |-------------|
| GPIO_Input    | Piano keys and switches (GPIO interrupts) |
| gpio_btn.c    | Initializes Piano Keys (external buttons) at Port E0-3 with interrupt and onboard switches at Port F0,4 with interrupt. It also initializes test LEDs.|
| speaker.c     | Initializes speaker. DIGITAL SYSTEM ONLY. |
| DAC.c         | Initalizes DAC with Port D0-3,6,7, sends data to DAC . ANALOGUE SYSTEM ONLY.|
| PLL.c         | Initializes PLL, sets clock frequency to 20MHz |
| Timer0A.c     | Initializes Timer0A with interrupt, declares up start and stop timer functions |
---
## Test Environment
- Hardware: TM4C123 LaunchPad, 4 external buttons, ~20 resistors (20k and 10k ohms), sound amplifier for analogue, speakers
- Clock: 20 MHz
- Tools: Keil, Visual Studio Code
- Observation: LEDs
---
## Module Test Cases (Add on with same format as needed)
### Module: GPIO Buttons
| Test ID       | Input         | Expected Output |
|-------        |-------        |-----------------|
| CR-003        | Nothing       | Set up PF0,4 with interrupt |
| CR-004        | Nothing       | Set up PE0,1,2,3 with interrupt |
| CR-006        | Nothing       | Conduct next test one-by-one for individual LED to turn on|
| **PIANO KEYS**    |               |               |
| TC-INT-001    | Press key     | Correct key detected in handler; Green LED on |
| TC-INT-009    | Hold Key      | Green LED stays on|
| TC-INT-001    | Release key   | Stop event detected; Green LED off |
|               |               |               |
| TC-INT-002    | Press key     | Correct key detected in handler; Red LED on |
| TC-INT-009    | Hold Key      | Red LED stays on|
| TC-INT-002    | Release key   | Stop event detected; Red LED off |
|               |               |               |
| TC-INT-003    | Press key     | Correct key detected in handler; Blue LED on   |
| TC-INT-009    | Hold Key      | Blue LED stays on|
| TC-INT-003    | Release key   | Stop event detected; Blue LED off   |
|               |               |               |
| TC-INT-004    | Press key     | Correct key detected in handler; Yellow LED on |
| TC-INT-009    | Hold Key      | Yellow LED stays on|
| TC-INT-004    | Release key   | Stop event detected; Yellow LED off |
| **ON-BOARD BTNS** |               |               |
| TC-MOD-001    | Press & release SW1     | Correct key detected in handler; Red LED turns on for low octave|
| TC-INT-005    | Press & release SW2     | Correct key detected in handler; Blue LED turns on for mid octave|
| TC-INT-005    | Press & release SW2     | Correct key detected in handler; Green LED turns on for high octave|
| TC-INT-005    | Press & release SW2     | Correct key detected in handler; Red LED turns on for low octave|
|               |               |               |
| TC-MOD-001    | Press & release SW1     | Correct key detected in handler (assume we start in song 1); Pink LED turns on for Song 1|
| TC-INT-013    | Nothing                 | Song is at the previously set octave |
| TC-INT-012    | Nothing                 | Repeats song until SW2 pressed |
| TC-INT-005    | Press & release SW2     | Correct key detected in handler ; Cyan LED turns on for Song 2|
| TC-INT-012    | Nothing                 | Repeats song until SW2 pressed |
| TC-INT-005    | Press & release SW2     | Correct key detected in handler; Yellow LED turns on for Song 3|
| TC-INT-012    | Nothing                 | Repeats song until SW2 pressed |
| TC-INT-005    | Press & release SW2     | Correct key detected in handler; Pink LED turns on for Song 1|
| TC-INT-012    | Nothing                 | Repeats song until SW2 pressed |
|               |               |               |
| TC-INT-006    | Press & release SW2   | Starts playing Song 1 in whatever octave it was last in |
| TC-INT-007    | Press & release RESET | Start Piano mode |
|               |               |               |
| TC-INT-010    | Press & release SW2     | Correct key detected in handler (assume we start in low); Blue LED turns on for mid octave|
| TC-INT-010    | Press & release SW2     | Correct key detected in handler; Green LED turns on for high octave|
| TC-INT-010    | Press & release SW2     | Correct key detected in handler; Red LED turns on for low octave|
|               |               |               |
| TC-INT-014    | Press & release SW2     | Correct key detected in handler; Cyan LED turns on for Song 2|
| TC-INT-014    | Press & release SW2     | Correct key detected in handler; Yellow LED turns on for Song 3|
| TC-INT-014    | Press & release SW2     | Correct key detected in handler; Pink LED turns on for Song 1|

Edge cases:
- Button debounce → single event only
- No input → no interrupts
- Assume no more than one piano key is pressed
Owner: Natasha Kho
Reviewer: Justin Naricso, Hanna Estrada
Acceptance: All events detected correctly

---
### Module: Timer + PLL
| Test ID       | Period | Expected |
|-------        |--------|----------|
| TC-SYS-001    | 20 Mhz | Run PLL at 20 Mhz |
| CR-001        | 20 Mhz | Set up, must have change timer reload function|
| CR-002        | 20 Mhz | Blink LED in handler; LED turns on for 1ms, turns off, turns on for 1ms |
| TC-SYS-001    | 20 Mhz | LED blinks at correct intreval when using reload for 20Mhz |
| CR-002        | 20 Mhz | Blink LED in handler; LED turns on for 0.5ms, turns off, turns on for 0.5ms |

Edge cases:
- Timer disabled → no toggles
- Invalid period → safe handling
Owner: Justin Narciso
Reviewer: Hanna Estrada, Natasha Kho
Acceptance: ±3% accuracy

---
## Module: DAC + Speaker
| Test ID | Period | Expected |
|------- |--------|----------|
| CR-005 | 20 Mhz | Speaker: Outputs a Squarewave in logic Analyzer |
| CR-006 | 20 Mhz | DAC: Calculated points are in a sin Wave when plotted |
| TC-INT-001 | 20 Mhz | C key pressed and C note is played |
| TC-INT-002 | 20 Mhz | D key pressed and D note is played |
| TC-INT-003 | 20 Mhz | E key pressed and E note is played |
| TC-INT-004 | 20 Mhz | F key pressed and F note is played |
| TC-INT-009 | 20 Mhz | When holding any of piano keys it plays the note until release |
| TC-INT-011 | 20 Mhz | Note frequencies match note in octaves |
| TC-INT-012 | 20 Mhz | Autoplay plays one of three songs(Mary had a Little Lamb, Twinkle Little Star, Happy Birthday) |
| TC-INT-013 | 20 Mhz | Selecting Auto-play starts the currently selected song based on octave |
| TC-INT-014 | 20 Mhz | In autoplay switch 2 round robins between songs |
| TC-INT-015 | 20 Mhz | Represent and play songs using provided note + duration tables (quarter note = 4 units). |
| TC-INT-016 | 20 Mhz | Speaker: Generate squarewave in logic analyzer with timer0A |
| TC-INT-017 | 20 Mhz | DAC:  generate sinwave with frequency matching notes |   

Edge cases:
- When there isnt an equal number of octaves and songs, make sure it functions still
- Ensure only one sound plays even when multiple piano buttons are pressed.
 
Owner: Hanna Estrada
Reviewer: Justin Narciso, Natasha Kho
Acceptance: Sound from the example project is played correctly. Should sound like previous demo/example projects.

## Evidence
Evidence stored in /evidence folder.
---