# Task 3 — Unions and Memory Layout: Weather-Station Sensor Packets (9 Marks)

- **Objective:** Design a memory-efficient sensor packet using a tagged union, predict and measure `sizeof`, complete `TODO 1`, and test union misuse.
- **Concepts Used:** `union` vs `struct`, tagged union (`enum kind` + `union`), alignment and padding, type-punning / inactive member misuse, `void*` vs separate-array storage.
- **Files Included:**
  - `Q3_Tagged_Union.c` — Supplied assignment program with `TODO 1` (`show()`) completed.
  - `Q3_Structure_Design.c` — Normal struct containing all 3 fields (`20` bytes).
  - `Q3_Union_Misuse.c` — Stores `31.5f` in `celsius` and reads `percent` (`1107034112` / `0x41FC0000`).
  - `Q3_Alternative_Storage.c` — Compares separate arrays and `void*` heap allocation.
  - `memory_layout.md`, `sizeof_results.csv`.
- **Compile & Run:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q3_Tagged_Union.c -o output/Q3_Tagged_Union
  ./output/Q3_Tagged_Union
  ```
- **Output Interpretation:** `sizeof union = 8, sizeof struct reading = 12`, followed by `Temp 31.5 C`, `Humidity 68 %`, `Status OK`. Saves 8 bytes per packet (40%) over the 20-byte normal struct.
- **Complexity:** Packet read/display is `O(1)` time and `O(1)` auxiliary space.
