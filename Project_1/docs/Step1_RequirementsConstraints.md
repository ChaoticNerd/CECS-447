# Step 1 – Requirements & Constraints
## Requirements

- #### System 1 (Digital output)
    - Outputs: Square Wave 
    - Contains Piano and Auto-play mode
    - Connect Speaker directly to board (PE4)


- #### System 2 (Analog Output)
    - Outputs: Sin Wave
    - 6-bit R2R DAC
        - Power Op-Amp (which connects to speaker)
    - 64-sample Sinusoid wavetable
    - Contains Piano and Auto-play mode


- #### Universal :rat:
    - [ ] Timer0A controls Tone
    - [ ] Piano Mode
        - [ ] Press-and-hold 1 of 4 keys to play a note
            - Double-edge interrupt system on input GPIO pins
            - Ports E0-3
            - System starts in lower C after reset
            - [ ] TEST: Toggle LED RED/BLUE/GREEN/PURPLE for each respective button hold
            - [ ] TEST: Use of a Tuning app to test notes
    
    - [ ] Auto-play Mode
        - Plays one of three songs at a time
        - Plays notes with different durations
            - [ ] TEST: Toggle LED between RED/BLUE for each note held, with metronome for comparison
        - SW2 changes song
        - Song loops until SW2 is pressed
        - [ ] EC: Input custom song
        
    - [ ] Switch 1 (Left Switch)
        - [ ] Toggle between Piano Mode and Auto-Play Mode
            - Single-edge interrupt system on input PF0
            - [ ] TEST: Toggle LED between BLUE/RED
            
    - [ ] Switch 2 (Right Switch)
        - Single-edge interrupt system on input PF4
        - In Piano Mode:
            - Changes Octave
            - [ ] TEST: Toggle LED RED/BLUE/GREEN for each octave
        - In Auto-Play Mode:
            - Changes Song
            - [ ] TEST: Toggle LED RED/BLUE/GREEN for each song


## Constraints
- General Constraints
    - [ ] Use any HARDWARE Timer for Sound
        - GPTIMER0A
    - [ ] System Clock is between 16Mhz and 80Mhz
        - Set to 20Mhz via PLL

- Use Interrupts for:
    - [ ] GPTIMER0A
    - [ ] Switch 1 - PF0
    - [ ] Switch 2 - PF4
    - [ ] Push Button 1 (Piano Key C) - PE0
    - [ ] Push Button 2 (Piano Key D) - PE1
    - [ ] Push Button 3 (Piano Key E) - PE2
    - [ ] Push Button 4 (Piano Key F) - PE3   
    - [ ] DAC on PD0-3 and PD6-7 (Connected to PB6 and PB7)
    

## Traceability
- Check Excel Sheet :bird:
- meow. meow. meow :cat::tada: