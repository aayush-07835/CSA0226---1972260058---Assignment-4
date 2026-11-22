# Testing Strategy — CSA02 CO4 Assignment 4

All programs were compiled using `gcc -std=c11 -Wall -Wextra -pedantic` (GCC 12.2.0) and executed with deterministic test inputs.

1. **Compiler Warning & Standard Compliance:** Every repaired and newly authored `.c` file compiled with zero errors and zero warnings under `-Wall -Wextra -pedantic`. `Q4_Original_Program.c` was separately compiled to capture the exact diagnostic error (`'p' is a pointer; did you mean to use '->'?`).
2. **Boundary & Negative Input Testing:**
   - *Task 1:* Tested valid 10-digit phones, 5-digit invalid phone rejection, and out-of-range age (`150`) rejection.
   - *Task 6:* Tested negative quantity (`-2`), nonexistent item ID (`999`), standalone stock overflow (`10 > 4`), and partial combo component shortage (`201` blocked by component `104` having `4 < 6`) to verify zero partial stock corruption.
3. **Expected Output Verification:**
   - *Task 2:* Verified exact sorted output `502`, `503`, `501` and `sizeof(struct parcel) = 44`.
   - *Task 3:* Verified `sizeof union = 8, sizeof struct reading = 12` and all three `show()` lines.
   - *Task 5:* Verified `static: 1001 1002 1003` and `auto  : 1001 1001 1001`, plus multi-file linking of `Q5_Extern_Main.c` and `Q5_Extern_Counter.c`.
4. **Empirical Evidence Logging:** All stdout outputs are archived in each task's `output/*_output.txt` and tabulated in the corresponding `.csv` files.
