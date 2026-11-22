# Task 1 — Data Design Review: Patient Register (6 Marks)

- **Objective:** Diagnose structural and data-modelling flaws in a primary health centre's parallel-array patient register and redesign it using nested C structures and structure pointers.
- **Concepts Used:** Parallel arrays (SoA) vs Array of Structures (AoS), nested `struct date` and `struct blood_pressure`, structure pointers (`->`), input validation, selection sort by age, `sizeof` memory analysis.
- **Files Included:**
  - `Q1_Original_Design.c` — Diagnostic demo of the original parallel-array flaws.
  - `Q1_Repaired_Structure.c` — Repaired nested-structure register with validation & sorting.
  - `Q1_Parallel_Arrays.c` — Repaired parallel-array alternative for swap & memory comparison.
  - `patient_test_data.csv`, `memory_comparison.csv` — Test cases and measured memory data.
- **Compile & Run:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q1_Repaired_Structure.c -o output/Q1_Repaired_Structure
  ./output/Q1_Repaired_Structure
  ```
- **Test Cases & Output:** Validates 5 valid patients and rejects invalid 5-digit phone and out-of-range age (`150`). Sorts patients ascending by age (`29, 35, 42, 54, 67`). `sizeof(struct patient) = 76` bytes (228 bytes copied per 3-assignment swap).
- **Complexity:** Selection sort is `O(n^2)` time, `O(1)` auxiliary space. AoS swaps 1 object (`76` B) per logical swap vs 8 separate array swaps in SoA.
