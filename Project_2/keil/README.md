# keil/ – Keil uVision Project Folder

This folder contains the Keil uVision project configuration files.

It connects the IDE to the source code located in the `/src` directory.

---

## 📁 Folder Structure

```
keil/
├── Project.uvprojx
├── Project.uvoptx
└── README.md
```


---

# 🔧 Purpose of This Folder

This folder stores:

- Keil project configuration (`.uvprojx`)
- Keil user settings (`.uvoptx`)
- Build configuration
- Target settings
- Compiler and linker configuration

This folder does **not** contain source code logic.

All firmware source code must remain in:
/src

---

# 🔄 Workflow Alignment

| Workflow Step | Uses Keil? |
|---------------|-----------|
| Step 1 – Requirements | No |
| Step 2 – Design | No |
| Step 3 – Module Testing | Yes (build & debug) |
| Step 4 – Integration | Yes (full system build) |
| Step 5 – Demo | Yes |

Keil is a build tool — not a design tool.

---

# 📌 Important Rules

- Do NOT move source files into this folder.
- Do NOT duplicate source files inside Keil directories.
- All `.c` and `.h` files must remain in `/src`.
- If adding new modules, update the Keil project to include them.
- Keep project paths relative (avoid absolute paths).

---

# 🧱 Recommended Practice

When adding new modules:

1. Create files inside:
   src/modules/
3. Add them to the Keil project (Project → Add Existing Files).
4. Keep drivers inside:
src/drivers/

Never place logic inside the Keil folder.

---

# 🏭 Industry Alignment

This mirrors professional embedded firmware repository structure:

- `/src` → Production firmware
- `/docs` → Documentation
- `/evidence` → Validation artifacts
- `/keil` → Toolchain configuration

Separating IDE configuration from source code improves:

- Maintainability
- Portability
- Repository cleanliness
- Team collaboration

---

# ⚠ Version Control Note

The `.gitignore` file is configured to ignore:

- Keil build artifacts
- Object files
- Listings
- Output binaries

Only project configuration files should be committed.

---

This folder supports building and debugging the firmware — it does not define system behavior.
