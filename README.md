# CSA02 – C Programming | Assignment 4 (CO4)
## Modelling Real-World Data with Structures and Unions

- **Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS)
- **Programme:** B.E / B.Tech
- **Course Code & Name:** CSA02 – C Programming
- **Course Outcome:** CO4 – Implement structures, unions and nested structures for modelling and processing real-world data
- **Student Name:** Aayush Nambiar T.
- **Register Number:** 1972260058
- **Nature of Assignment:** Individual (50 Marks)
- **Compiler & Standard:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0` with `-std=c11 -Wall -Wextra -pedantic`

---

## Repository Structure

```text
CSA02_CO4_Assignment_4/
├── README.md
├── SUMMARY.md
├── Assignment_Report.docx
├── Assignment_Report.pdf
├── Task01_Patient_Register_Design/
├── Task02_Courier_Parcel_Tracking/
├── Task03_Weather_Station_Union/
├── Task04_Bank_Account_Forensics/
├── Task05_Storage_Classes/
├── Task06_Canteen_Inventory_Billing/
└── Documentation/
```

---

## Compilation & Execution Instructions

Every C program in this repository is written in standard C11 and compiles cleanly with `-Wall -Wextra -pedantic` (except `Q4_Original_Program.c`, which is intentionally preserved with its original `p.number` defect for forensic analysis).

### Task 1 — Patient Register Design (6 Marks)
```bash
cd Task01_Patient_Register_Design
gcc -std=c11 -Wall -Wextra -pedantic Q1_Original_Design.c -o output/Q1_Original_Design && ./output/Q1_Original_Design
gcc -std=c11 -Wall -Wextra -pedantic Q1_Repaired_Structure.c -o output/Q1_Repaired_Structure && ./output/Q1_Repaired_Structure
gcc -std=c11 -Wall -Wextra -pedantic Q1_Parallel_Arrays.c -o output/Q1_Parallel_Arrays && ./output/Q1_Parallel_Arrays
```

### Task 2 — Courier Parcel Tracking (8 Marks)
```bash
cd Task02_Courier_Parcel_Tracking
gcc -std=c11 -Wall -Wextra -pedantic Q2_Parcel_Tracking.c -o output/Q2_Parcel_Tracking && ./output/Q2_Parcel_Tracking
gcc -std=c11 -Wall -Wextra -pedantic Q2_Nested_Structure.c -o output/Q2_Nested_Structure && ./output/Q2_Nested_Structure
gcc -std=c11 -Wall -Wextra -pedantic Q2_Flat_Structure.c -o output/Q2_Flat_Structure && ./output/Q2_Flat_Structure
```

### Task 3 — Weather-Station Sensor Packets (9 Marks)
```bash
cd Task03_Weather_Station_Union
gcc -std=c11 -Wall -Wextra -pedantic Q3_Tagged_Union.c -o output/Q3_Tagged_Union && ./output/Q3_Tagged_Union
gcc -std=c11 -Wall -Wextra -pedantic Q3_Structure_Design.c -o output/Q3_Structure_Design && ./output/Q3_Structure_Design
gcc -std=c11 -Wall -Wextra -pedantic Q3_Union_Misuse.c -o output/Q3_Union_Misuse && ./output/Q3_Union_Misuse
gcc -std=c11 -Wall -Wextra -pedantic Q3_Alternative_Storage.c -o output/Q3_Alternative_Storage && ./output/Q3_Alternative_Storage
```

### Task 4 — Bank Account Forensics (7 Marks)
```bash
cd Task04_Bank_Account_Forensics
# Q4_Original_Program.c intentionally fails to compile (p.number error)
gcc -std=c11 -Wall -Wextra -pedantic Q4_Pass_By_Value.c -o output/Q4_Pass_By_Value && ./output/Q4_Pass_By_Value
gcc -std=c11 -Wall -Wextra -pedantic Q4_Pointer_Repair.c -o output/Q4_Pointer_Repair && ./output/Q4_Pointer_Repair
gcc -std=c11 -Wall -Wextra -pedantic Q4_Const_Pointer.c -o output/Q4_Const_Pointer && ./output/Q4_Const_Pointer
```

### Task 5 — Storage Classes: Hostel Mess Counter (7 Marks)
```bash
cd Task05_Storage_Classes
gcc -std=c11 -Wall -Wextra -pedantic Q5_Auto_Counter.c -o output/Q5_Auto_Counter && ./output/Q5_Auto_Counter
gcc -std=c11 -Wall -Wextra -pedantic Q5_Static_Counter.c -o output/Q5_Static_Counter && ./output/Q5_Static_Counter
gcc -std=c11 -Wall -Wextra -pedantic Q5_Extern_Main.c Q5_Extern_Counter.c -o output/Q5_Extern_Counter && ./output/Q5_Extern_Counter
gcc -std=c11 -Wall -Wextra -pedantic Q5_Register_Loop.c -o output/Q5_Register_Loop && ./output/Q5_Register_Loop
gcc -std=c11 -Wall -Wextra -pedantic Q5_Two_Independent_Counters.c -o output/Q5_Two_Independent_Counters && ./output/Q5_Two_Independent_Counters
```

### Task 6 — College Canteen Inventory & Billing (13 Marks)
```bash
cd Task06_Canteen_Inventory_Billing
gcc -std=c11 -Wall -Wextra -pedantic Q6_Canteen_Main.c -o output/Q6_Canteen_Main && ./output/Q6_Canteen_Main
gcc -std=c11 -Wall -Wextra -pedantic Q6_Alternative_Linked_List.c -o output/Q6_Alternative_Linked_List && ./output/Q6_Alternative_Linked_List
gcc -std=c11 -Wall -Wextra -pedantic Q6_Benchmark.c -o output/Q6_Benchmark && ./output/Q6_Benchmark
```

---

## Verified Key Outputs & Evidence

| Task | Key Verified Result | Evidence File |
| :--- | :--- | :--- |
| Task 1 | `sizeof(struct patient) = 76` B (7600 B for 100); `Q1_Parallel_Arrays` = 7504 B; 228 B/swap | `Task01_Patient_Register_Design/memory_comparison.csv` |
| Task 2 | `502 1.2 kg Chennai-600077 12/10/2026`, `503 2.8 kg Coimbatore-641001 13/10/2026`, `501 4.5 kg Madurai-625001 12/10/2026`; `sizeof(struct parcel) = 44` B (132 B/swap) | `Task02_Courier_Parcel_Tracking/structure_size_comparison.csv` |
| Task 3 | `sizeof union = 8, sizeof struct reading = 12`; `Temp 31.5 C`, `Humidity 68 %`, `Status OK`; misuse `31.5f` -> `1107034112` (`0x41FC0000`) | `Task03_Weather_Station_Union/sizeof_results.csv` |
| Task 4 | `&list[0] = 0x7fffdd14c340` vs `&a = 0x7fffdd14c328` (pass-by-value copy); repaired pointer updates balances to `5200.00`, `12480.00`, `832.00` | `Task04_Bank_Account_Forensics/address_evidence.csv` |
| Task 5 | `static: 1001 1002 1003`, `auto: 1001 1001 1001`; single `printf` evaluated RHS-to-LHS (`1006 1005 1004`); `extern` linked across 2 `.c` files | `Task05_Storage_Classes/storage_class_comparison.csv` |
| Task 6 | Atomic combo rollback verified; expiry warning (`13/10/2026`, 1 day left); revenue-sorted bill (`Rs. 450.00`); `CanteenItem` 76 B vs `ItemNode` 88 B | `Task06_Canteen_Inventory_Billing/billing_results.csv` |

---

## GitHub Submission Instructions

1. Create a repository named `CSA02-1972260058-Assignment4` on GitHub.
2. Push each task folder progressively with meaningful commit messages (at least one commit per task).
3. Capture local terminal window screenshots of each executed program into the respective `screenshots/` folders if required by your faculty.
4. Fill in the GitHub repository link and submission date on the cover page of `Assignment_Report.docx` / `Assignment_Report.pdf`.
