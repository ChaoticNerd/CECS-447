# Step 5 – Integration & End-to-End Testing (CER)

## Overview
All modules were integrated into the full system and validated using end-to-end tests.  
Evidence files are stored in `/evidence/` and linked below.

---
## Claim–Evidence–Reasoning (CER)

### Claim 1 (R1)
**Claim:** Digital system, Piano mode plays correct notes when keys are held down and stops when released.  
**Evidence:** `/evidence/R1 S1 Piano Keys.mov`  
**Reasoning:** Pressing button plays a note, releasing the button stops the note.
R1 // E2E: Playing random notes on the piano

### Claim 2 (R2)
**Claim:**  Analogue system, Piano mode plays correct notes when keys are held down and stops when released.  
**Evidence:** `/evidence/R2 S2 Piano Buttons.mov`
**Reasoning:** Pressing button plays a note, releasing the button stops the note.

### Claim 3 (R3, R4, R5)
**Claim:** Analogue AND Digital System, on-board buttons cycle through octaves or songs and modes when pressed.
**Evidence:** `/evidence/R3 S1 Octave Switch.mov`, `/evidence/R3 S2 Octave Switch.mov`, `/evidence/R4 S1 Song Switch.mov`, `/evidence/R4 S2 Song Switch.mov`, `/evidence/R5 S1 Mode Switch.mov`, `/evidence/R5 S2 Mode Switch.mov`
**Reasoning:** pressing Switch 2 changes between piano and auto mode, and pressing switch 1 changes octave or song depending on which current mode.

### Claim 4 (R6)
**Claim:** Digital System, Auto-play mode plays all songs from start to end and loops.
**Evidence:** `/evidence/R6 S1 All Songs.mp4`
**Reasoning:** Entering Auto-play mode plays full song; song loops when it ends.

### Claim 5 (R7)
**Claim:** Analogue System, Auto-play mode plays all songs from start to end and loops.
**Evidence:** `/evidence/R7 S2 All Songs.mov`
**Reasoning:** Entering Auto-play mode plays full song; song loops when it ends.

### Claim 6 (R8)
**Claim** Analogue AND Digital System, changing octave in Piano mode changes octave of song mode.
**Evidence:** `/evidence/R8 S1 Octave Song Change.mov`, `/evidence/R8 S2 Octave Song Change.mov`
**Reasoning** Beginning note of Mary Had A Little Lamb is E4, changing to octave 5 makes the song begin at E5.
// P: playing a song in O4, going back to piano mode, changing octave, playing same song in O5

### Claim 7 (R9)
**Claim** Analogue AND Digital System, Auto-play mode plays an extra, custom song from start to end, and loops.
**Evidence:** `/evidence/R9 S1 Memory by Toby Fox.mov`, `/evidence/R9 S2 Memory by Toby Fox.mov`
**Reasoning** System plays four songs, fourth song is custom song.

---

## Test Matrix
| Requirement | Test Method | Evidence |
|-------------|------------|----------|
| R1 : Pressing Piano Keys plays correlated note, stops when released (Digital) | End-to-end test | `/evidence/R1 S1 Piano Keys.mov` |
| R2 : Pressing Piano Keys plays correlated note, stops when released (Analogue) | End-to-end test | `/evidence/R2 S2 Piano Buttons.mov` |
| R3 : Switch 2 changes octave in Piano mode       | Performance test | `/evidence/R3 S1 Octave Switch.mov`, `/evidence/R3 S2 Octave Switch.mov` |
| R4 : Switch 2 changes song in Auto-play mode       | Performance test | `/evidence/R4 S1 Song Switch.mov`, `/evidence/R4 S2 Song Switch.mov` |
| R5 : Switch 1 switches between Piano and Auto mode         | End-to-end test | `/evidence/R5 S1 Mode Switch.mov`, `/evidence/R5 S2 Mode Switch.mov` |
| R6 : Can play 3 songs in autoplay mode, song loops upon ending (Digital)       | Performance test | `/evidence/R6 S1 All Songs.mp4` |
| R7 : Can play 3 songs in autoplay mode, song loops upon ending (Analogue)        | Performance test | `/evidence/R7 S2 All Songs.mov` |
| R8 : Song can play in different octaves        | Performance test | `/evidence/R8 S1 Octave Song Change.mov`, `/evidence/R8 S2 Octave Song Change.mov` |
| R9 : (Extra Credit) Add a fourth song to autoplay mode        | End-to-end test | `/evidence/R9 S1 Memory by Toby Fox.mov`, `/evidence/R9 S2 Memory by Toby Fox.mov` |
---

## Rejected AI Suggestion
We didn't use AI.

---

## Logs Updated
- Decision log updated with rejected optimization.
- AI-use log updated.

---