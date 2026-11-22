# Task 4 — Structure Forensics: Bank Account Interest Program (7 Marks)

- **Objective:** Diagnose pass-by-value and pointer-operator defects in a bank account program, prove pass-by-value copying using memory addresses, and repair the code using structure pointers.
- **Concepts Used:** Pass-by-value vs pass-by-pointer, `.` vs `->` operator, `const struct account *`, stack address evidence.
- **Files Included:**
  - `Q4_Original_Program.c` — Original defective code (intentionally fails compilation on `p.number`).
  - `Q4_Pass_By_Value.c` — Address evidence (`&list[0]` vs `&a`) + return-by-value alternative.
  - `Q4_Pointer_Repair.c` — Repaired pointer-based program updating balances by 4%.
  - `Q4_Const_Pointer.c` — Demonstrates `const` pointer for read-only functions.
  - `address_evidence.csv`, `performance_comparison.csv`.
- **Compile & Run:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q4_Pointer_Repair.c -o output/Q4_Pointer_Repair
  ./output/Q4_Pointer_Repair
  ```
- **Output Interpretation:** Original balances `5000.00`, `12000.00`, `800.00` update to `5200.00`, `12480.00`, `832.00` when passed by pointer (`a == &list[i]`).
- **Complexity:** `O(1)` per account update (`O(n)` for `n` accounts).
