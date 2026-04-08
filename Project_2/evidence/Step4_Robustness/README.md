# Step 4 – Robustness & System-Level Evidence

This folder contains robustness and system-level validation evidence.

## 📁 Naming Convention

All files must follow:

`[TYPE]-[ID]_[ModuleOrFeature]_[ShortDescription].[ext]`

For Step 4:

TYPE = ROB (robustness test)  -- BASICALLY EDGE CASES
TYPE = SYS (system-level integration test) -- Mode 1, Mode 2, Mode 3

Examples:

- ROB-01_Sensor_NoEcho.png  
- ROB-02_Switch_DebounceTest.mp4  
- SYS-03_FullSystem_NormalDistance.png  


ROB-01_InvalidInputMainMenu
ROB-02_MultipleNumbers_Mode2
ROB-03_MultipleNumbers_Mode1_2
ROB-04_Multiple

## Rules

- ID must match your System-Level or Robustness Test ID.
- ModuleOrFeature must indicate what part of the system is being validated.
- Description must clearly state the condition tested.
- Files must map to your integration test matrix or CER section.
