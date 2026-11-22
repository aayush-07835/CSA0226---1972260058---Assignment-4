# Assignment Summary — CSA02 CO4 Assignment 4

**Student:** Aayush Nambiar T. (`1972260058`)  
**Total Marks:** 50 | **Tasks Completed:** 6 / 6 (100% Individual Work)  
**Compiler:** GCC 12.2.0 (`-std=c11 -Wall -Wextra -pedantic`)

## Quick Overview by Task

1. **Task 1 — Patient Register Design (6 Marks):** Diagnosed 7 defects in the parallel-array register (phone truncation in `char[10]`, ambiguous `float bp`, 8-char date overflow, missing `count` bounds check, global state, and painful multi-array sorting). Redesigned with nested `struct date`, `struct blood_pressure`, and `struct patient` (76 bytes), pointer-based `addPatient()`, input validation, and age sorting.
2. **Task 2 — Courier Parcel Tracking (8 Marks):** Modelled `Date`, `Address`, `Person`, `ServiceType`, and `Parcel` (`140` bytes full model; `44` bytes in `Q2_Parcel_Tracking.c`). Completed `TODO 1` (`print_parcel` with `->`) and `TODO 2` (selection sort by weight, 2 swaps, 132 bytes copied per swap). Verified exact expected output and compared against `Q2_Flat_Structure.c`.
3. **Task 3 — Weather-Station Sensor Packets (9 Marks):** Implemented `Q3_Tagged_Union.c` (`sizeof union = 8`, `sizeof struct reading = 12` — 40% smaller than the 20-byte normal struct). Completed `TODO 1` (`switch (r->type)`), ran the misuse experiment (`31.5f` read as `int` = `1107034112` / `0x41FC0000`), and compared with separate arrays and `void*` heap packets.
4. **Task 4 — Bank Account Forensics (7 Marks):** Captured the GCC compile error on `p.number`, proved pass-by-value copying via stack addresses (`0x7fffdd14c340` vs `0x7fffdd14c328`), repaired `addInterest()` using `struct account *` and `->` (updating balances to `5200.00`, `12480.00`, `832.00`), and contrasted pass-by-value, pointer, and `const` pointer semantics.
5. **Task 5 — Storage Classes: Mess Token Counter (7 Marks):** Implemented `auto`, `static`, two-file `extern`, and `register` versions; completed `TODO 1` (`static: 1001 1002 1003`, `auto: 1001 1001 1001`); demonstrated unspecified argument evaluation order (`1006 1005 1004` on GCC x86_64); extended all versions to independent Veg/Non-Veg counters; and compared against `int next_token_ptr(int *counter)`.
6. **Task 6 — College Canteen Inventory & Billing (13 Marks):** Designed and built a complete tagged-union inventory and billing system supporting packaged, cooked, and 3-component combo items, atomic combo stock validation, 2-day expiry warnings, and revenue-sorted daily billing (`Rs. 450.00` across 8 test transactions). Benchmarked against a singly linked list (`76` B vs `88` B per item).
