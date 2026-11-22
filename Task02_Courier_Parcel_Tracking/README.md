# Task 2 — Courier Parcel Tracking with Nested Structures (8 Marks)

- **Objective:** Model a courier franchise parcel-tracking system using nested structures, complete `TODO 1` and `TODO 2`, verify access paths, and compare against a flat structure.
- **Concepts Used:** Nested structures (`Date`, `Address`, `Person`, `Parcel`), `typedef`, `enum ServiceType`, structure pointers (`->`), selection sort by weight, `sizeof`.
- **Files Included:**
  - `Q2_Parcel_Tracking.c` — Supplied assignment program with `TODO 1` & `TODO 2` completed.
  - `Q2_Nested_Structure.c` — Full entity model with sender, receiver, service type, charge, and city filter.
  - `Q2_Flat_Structure.c` — Flat-structure alternative for comparison.
  - `parcel_test_data.csv`, `structure_size_comparison.csv`.
- **Compile & Run:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q2_Parcel_Tracking.c -o output/Q2_Parcel_Tracking
  ./output/Q2_Parcel_Tracking
  ```
- **Output Interpretation:** Produces exact expected sorted order (`502 1.2 kg Chennai-600077 12/10/2026`, `503 2.8 kg Coimbatore-641001 13/10/2026`, `501 4.5 kg Madurai-625001 12/10/2026`). `sizeof(struct parcel) = 44` bytes; 2 swaps copy `132` bytes each.
- **Complexity:** Sorting is `O(n^2)` time, `O(1)` auxiliary space; city filtering is `O(n)`.
