# Task 6 — Design Challenge: College Canteen Inventory & Billing (13 Marks)

- **Objective:** Independently design and implement a College Canteen Inventory & Billing System supporting packaged, cooked, and combo items, atomic stock updates, 2-day expiry warnings, and revenue-sorted daily billing.
- **Concepts Used:** Nested structures, tagged union (`enum ItemType` + `union details`), arrays of structures, structure pointers, atomic validation, date arithmetic, selection sort, singly linked list alternative & benchmark.
- **Files Included:**
  - `Q6_Canteen_Main.c` — Complete system demonstrating all 10 required test cases.
  - `Q6_Alternative_Linked_List.c` — Dynamically allocated singly linked list alternative.
  - `Q6_Benchmark.c` — Memory & search-time benchmark (`N = 50, 500, 5000`).
  - `sample_inventory.csv`, `sample_sales.csv`, `expiry_test_cases.csv`, `billing_results.csv`, `performance_comparison.csv`.
- **Compile & Run:**
  ```bash
  gcc -std=c11 -Wall -Wextra -pedantic Q6_Canteen_Main.c -o output/Q6_Canteen_Main
  ./output/Q6_Canteen_Main
  ```
- **Output Interpretation:** Flags Mango Juice (`13/10/2026`, 1 day left), processes valid sales, atomically blocks Lunch Combo (`201`) when component `104` has insufficient stock, and prints revenue-sorted bill totaling `Rs. 450.00`.
- **Complexity:** Item lookup `O(n)`, daily summary sort `O(n^2)` (`O(1)` aux space). Array item = `76` B vs Linked List node = `88` B.
