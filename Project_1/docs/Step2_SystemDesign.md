# Step 2 — System Design 

**Project:** CECS 447 – Digital Piano

**Purpose:** Template for documenting Digital Signal Generation (solution A) and Analog Signal Generation (solution B). It lists the Hardware and Software components required for both parts.

---

## Solution A — Digital Signal Generation

Solution A outputs a digital square wave directly to a speaker. By using a hardware timer with a specific reload value, we can send electric signals to the speaker at a frequency matching the pitch we want to output. The output is dependent on the mode - auto-play or piano mode - and in piano mode, there's four external buttons that control which note is played.

---

## 1. Hardware Design

### GPIO Pin Assignment
**GPIO PINS**
  - Inputs:
    - Single Edge Interrupt
      - Switch 1 - PF0
      - Switch 2 - PF4
    - Double Edge Interrupt
      - EXTERNAL Push Button 1 (Piano Key C) - PE0
      - EXTERNAL Push Button 2 (Piano Key D) - PE1
      - EXTERNAL Push Button 3 (Piano Key E) - PE2
      - EXTERNAL Push Button 4 (Piano Key F) - PE3
  - Ouputs:
    - EXTERNAL Speaker Vin (Output) - PE4

![Hardware Diagram System 1](/docs/image/Hardware-S1.png "Hardware Diagram System 1")

---

### Peripherals Used
- Speaker - Connected to PE4 to play sound
- Buttons - Inputs for Piano Mode input (PE0,1,2,3)
  -  Push Button 1 (Piano Key C) - PE0
  -  Push Button 2 (Piano Key D) - PE1
  -  Push Button 3 (Piano Key E) - PE2
  -  Push Button 4 (Piano Key F) - PE3
- Board buttons 
  - Switching mode (PF0) 
  - Switching song (Autoplay) / octave (Piano) (PF4)

---

### External Components
- Speaker - Connected to PE4 to play sound (Output)
- 4 Buttons - Inputs for Piano Mode input (PE0,1,2,3)
  -  Push Button 1 (Piano Key C) - PE0
  -  Push Button 2 (Piano Key D) - PE1
  -  Push Button 3 (Piano Key E) - PE2
  -  Push Button 4 (Piano Key F) - PE3

---

## 2. Software Architecture

### Modules and Interfaces(API)

- main.c :
  - main(); - Handles whether the system is in piano mode or autoplay mode, is responsible for setting which note is played.
- Timer0A.c / .h
  - Timer0A_Init(); - Initializes hardware timer.
- switches.c / .h
  - Switches_Init(); - Initializes all buttons and speaker.
- PLL.c / .h
  - PLL_Init(); - Initializes PLL, sets timer frequency to 20Mhz.

---

### Data Flow
#### PIANO MODE
![Data Flow Graph Piano](/docs/image/Dataflow-S1Piano.png "Data Flow Graph Piano System 1")

#### AUTOPLAY MODE
![Data Flow Graph Autoplay](/docs/image/Dataflow-S1Autoplay.png "Data Flow Graph Autoplay System 1")

---

### Call Graph
![Call Graph System 1](/docs/image/Call-S1.png "Call Graph System 1")

---

## 3. Timing and Accuracy Considerations

The clock source used is Timer0A, which runs at a frequency of 20Mhz due to PLL.
This allows for a reload value to in the range of the 32-bit general purpose timer.
The general purpose timer is used for determining note frequency by the general purpose reload value, and
this is because its a hardware timer and allows for accurate tones.
whilst we use a software timer for a tempo as it is no required to be as accurate as tones.
Another consideration for tone accuracy, is that in digital values its sampled at specific frequencies and cannot make tone between notes.
Another consideration for tone is the Nyquist Sampling theorem in which to properly sample the frequency must be sampled specificly twice as fast as the note frequency if else results in an aliasing error whichy will play a tone that is not intended.

---

## 4. Advantages and Tradeoffs

### Advantages
- Less hardware connections
  - No audio amplifier
  - No R-2R ladder
- No DAC.c/.h
- More accurate timing due to sending signals straight to speaker
  - Doesn't need to pass through a DAC which might have varying resistor values

### Tradeoffs
- Requires sampling due to not converting to analog sine wave
  - May have inaccuracies due to sampling from sine wave
  - Decreased scale due to sampling at certain points instead of a whole sine wave
- Sampling software using the Nyquist's Sampling Theorem
  - Time quantization; sampling 2x as fast as the signal is oscillating

---

## 5. Intended Use

The purpose of this system is to act as a comparative alternative to Solution B, which outputs analog sine waves to make sound. This system is more precise; however, it comes at the cost of having a smaller range of notes.

---

## Solution B — Analogue Signal Generation

Solution B outputs an analogue sine wave to an amplifier and bumps up the voltage for the speaker. By using a hardware timer with a specific reload value, we can send electric signals to the speaker at a frequency matching the pitch we want to output. The output is dependent on the mode - auto-play or piano mode - and in piano mode, there's four external buttons that control which note is played.

---

## 1. Hardware Design

### GPIO Pin Assignment
**GPIO PINS**
  - Inputs:
    - Single Edge Interrupt
      - Switch 1 - PF0
      - Switch 2 - PF4
    - Double Edge Interrupt
      - EXTERNAL Push Button 1 (Piano Key C) - PE0
      - EXTERNAL Push Button 2 (Piano Key D) - PE1
      - EXTERNAL Push Button 3 (Piano Key E) - PE2
      - EXTERNAL Push Button 4 (Piano Key F) - PE3
  - Ouputs:
    - EXTERNAL DAC GPIO - PD0
    - EXTERNAL DAC GPIO - PD1
    - EXTERNAL DAC GPIO - PD2
    - EXTERNAL DAC GPIO - PD3
    - EXTERNAL DAC GPIO - PD6
    - EXTERNAL DAC GPIO - PD7

![Hardware Diagram System 2](/docs/image/Hardware-S2.png "Hardware Diagram System 2")

---

### Peripherals Used
- DAC     - Convert 6 digital signals (PD0,1,2,3,6,7) into analogue signals
  - PD0 output bit 0
  - PD1 output bit 1
  - PD2 output bit 2
  - PD3 output bit 3
  - PD6 output bit 4
  - PD7 output bit 5
- Speaker - Connected to DAC to play sound
- Buttons - Inputs for Piano Mode input (PE0,1,2,3)
  -  Push Button 1 (Piano Key C) - PE0
  -  Push Button 2 (Piano Key D) - PE1
  -  Push Button 3 (Piano Key E) - PE2
  -  Push Button 4 (Piano Key F) - PE3
- Board buttons - Inputs for switching mode (PF0) and switching song/octave (PF4)

---

### External Components
- DAC (Outputs)
  - PD0 output bit 0
  - PD1 output bit 1
  - PD2 output bit 2
  - PD3 output bit 3
  - PD6 output bit 4
  - PD7 output bit 5
- Speaker - Connected to DAC to play sound (Output)
- 4 Buttons - Inputs for Piano Mode input (PE0,1,2,3)
  -  Push Button 1 (Piano Key C) - PE0
  -  Push Button 2 (Piano Key D) - PE1
  -  Push Button 3 (Piano Key E) - PE2
  -  Push Button 4 (Piano Key F) - PE3

---

## 2. Software Architecture

### Modules and Interfaces(API)

- main.c :
  - main(); - Handles whether the system is in piano mode or autoplay mode, is responsible for setting which note is played.
- Timer0A.c / .h
  - Timer0A_Init(); - Initializes hardware timer.
- switches.c / .h
  - Switches_Init(); - Initializes all buttons and speaker.
- PLL.c / .h
  - PLL_Init(); - Initializes PLL, sets timer frequency to 20Mhz.
- DAC.c / .h
  - DAC_Out(); - Outputs digital data to pins to convert to analog data.

---

### Data Flow
#### Data Flow Graph (Piano)
  ![Data Flow Graph Piano](/docs/image/Dataflow-S2Piano.png "Data Flow Graph Piano System 2")

#### Data Flow Graph (Autoplay)
  ![Data Flow Graph Autoplay](/docs/image/Dataflow-S2Autoplay.png "Data Flow Graph Autoplay System 2")

---

### Call Graph
![Call Graph System 2](/docs/image/Call-S2.png "Call Graph System 2")

---

## 3. Timing and Accuracy Considerations

The clock source used is Timer0A, which runs at a frequency of 20Mhz due to PLL.
This allows for a reload value to in the range of the 32-bit general purpose timer.
The general purpose timer is used for determining note frequency by the general purpose reload value, and
this is because its a hardware timer and allows for accurate tones.
whilst we use a software timer for a tempo as it is no required to be as accurate as tones.
Another consideration for tone accuracy, is that since its not sampled therefore requires a more accurate input so that it does not play a tone inbetween notes.

---

## 4. Advantages and Tradeoffs

### Advantages
- More accurate sound bytes due to following analog sine wave
- Wider range of notes
- No sampling in software

### Tradeoffs
- More processing for microcontroller
  - Due to larger range of notes, must be more precise for each note
- Resistors vary in manufacturing
  - May lead to incorrect frequencies and pitch

---

## 5. Intended Use

The purpose of this solution is to act as a comparative alternative to Solution A, which outputs digital square waves to make sound. This system is more accurate; however, it is less precise due to variable resistors, and it requires more processing power.

--

