# Task 5 — Storage Classes: Hostel Mess Token Counter (7 Marks)

- **Objective:** Implement a hostel mess token counter (starting at 1001) using `auto`, `static`, `extern`, and `register`, adapt to two independent counters (Veg & Non-Veg), and test argument evaluation order.
- **Concepts Used:** `auto`, `static`, `extern` (multi-file linkage), `register`, unspecified evaluation order of function arguments, caller-owned pointer alternative (`int *counter`).
- **Files Included:**
  - `Q5_Auto_Counter.c`, `Q5_Static_Counter.c`, `Q5_Extern_Main.c`, `Q5_Extern_Counter.c`, `Q5_Register_Loop.c`, `Q5_Two_Independent_Counters.c`.
  - `storage_class_comparison.csv`.
- **Compile & Run (Multi-file extern):**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q5_Extern_Main.c Q5_Extern_Counter.c -o output/Q5_Extern_Counter
  ./output/Q5_Extern_Counter
  ```
- **Output Interpretation:** `static: 1001 1002 1003`, `auto: 1001 1001 1001`. Single `printf` printed `1006 1005 1004` (GCC x86_64 evaluated arguments right-to-left, proving evaluation order is unspecified in C).
- **Complexity:** `O(1)` time and `O(1)` space per token issue across all approaches.
