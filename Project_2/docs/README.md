# docs/ – Project Documentation Folder

This folder contains all documentation required for the 5-Step Embedded Systems Workflow.

Each file corresponds directly to one phase of the engineering process.  
Do not rename or delete these files.

---

# 📁 Documentation Structure

```
docs/
├── AI_Log.md
├── Step1_Requirements.md
├── Step2_System_Design.md
├── Step3_Module_Test_Report.md
└── Step4_System_Integration_Report.md
```


# 🔄 Workflow Mapping

| Workflow Step | File |
|---------------|------|
| Step 1 – Requirements & Constraints | `Step1_Requirements.md` |
| Step 2 – System Design & Module Planning | `Step2_System_Design.md` |
| Step 3 – Module Implementation & Testing | `Step3_Module_Test_Report.md` |
| Step 4 – Integration & Verification | `Step4_System_Integration_Report.md` |
| AI Usage Tracking | `AI_Log.md` |

---

# 🔹 File Descriptions

## Step1_Requirements.md

Contains:

- Functional requirements (clear and measurable)
- System constraints (timing, memory, hardware limits)
- AI verification summary

This is equivalent to an industry **System Requirements Specification (SRS)**.

---

## Step2_System_Design.md

Contains:

- Two possible system designs
- Hardware plan (GPIO, peripherals, components)
- Software feature implementation method (FSM, interrupt-driven, etc.)
- Final module list
- Module responsibilities
- Task assignment

This corresponds to an industry **Architecture Design Review document**.

---

## Step3_Module_Test_Report.md

Contains:

- Module-Level Traceability Table
Requirement → Responsible Module → Module Test Evidence
- Module test results
- Normal test cases
- Edge case tests

This reflects an industry **Unit Verification Report**.

---

## Step4_System_Integration_Report.md

Contains:

- Integration order explanation
- Final call graph
- Final data flow diagram
- System-Level Traceability Table  

Requirement → System Test Method → Evidence → Pass/Fail
- CER Lite (Claim–Evidence–Reasoning)
- Robustness test description
- AI verification summary

This reflects an industry **System Validation Report**.

---

## AI_Log.md

Tracks:

- All AI usage
- Prompts used
- What was accepted/rejected
- Debugging assistance

AI Policy Reminder:

- AI is allowed for verification and debugging only.
- AI is NOT allowed to generate production code in Steps 3 and 4.

---

# 🏗 Industry Alignment

This documentation structure mirrors professional embedded development practices:

- Requirements → Architecture → Unit Testing → Integration → Validation
- Clear traceability from requirement to test evidence
- Separation of documentation from source code
- Professional verification discipline

Maintaining this structure ensures:

- Clean grading
- Clear validation path
- Reduced integration confusion
- Professional engineering habits

---

# 📌 Important Rules

- Keep documentation concise but complete.
- Update traceability tables when changes occur.
- Do not mix source code into documentation files.
- Maintain clear mapping between evidence and reports.

---

This folder represents the engineering thinking behind the code.


