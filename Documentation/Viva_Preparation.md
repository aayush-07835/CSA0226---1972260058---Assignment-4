# Viva Preparation — CSA02 CO4 Assignment 4

## Section A: Structures, Nested Structures, Arrays & Pointers (12 Q&As)

1. **Q: What is the difference between a structure declaration and a structure variable definition?**  
   **A:** A declaration (`struct date { int day, month, year; };`) defines a blueprint (type) without allocating memory; a variable definition (`struct date d;`) allocates memory for an instance.
2. **Q: Why do we use `typedef` with structures?**  
   **A:** It creates a clean type alias (e.g., `typedef struct { ... } Parcel;`), avoiding repeated `struct` keywords in function signatures and arrays.
3. **Q: Why group related fields in a structure instead of parallel arrays?**  
   **A:** A structure keeps one entity's fields contiguous in memory, preventing index desynchronization during sorting, insertion, or deletion.
4. **Q: What is a nested structure?**  
   **A:** A structure that contains another structure as a member (e.g., `struct parcel` containing `struct address` and `struct date`), enabling modular reuse.
5. **Q: How do you access a nested member using (a) a structure variable and (b) a structure pointer?**  
   **A:** With a variable, use chained dots (`bookings[2].receiver.addr.pincode`); with a pointer, use `->` on the pointer and `.` on embedded sub-structs (`(ptr + 2)->receiver.addr.pincode`).
6. **Q: What is the difference between `.` and `->`?**  
   **A:** `.` accesses a member of a structure *object*; `->` dereferences a structure *pointer* and accesses its member (`p->x` is equivalent to `(*p).x`).
7. **Q: Why did `p.number` fail to compile in Task 4?**  
   **A:** Because `p` was declared as `struct account *p` (a pointer), not a `struct account` object.
8. **Q: Why did `addInterest(list[i], 4)` leave balances unchanged in Task 4?**  
   **A:** C passes structures by value, copying `list[i]` to a new stack address (`0x7fffdd14c328` vs `0x7fffdd14c340`), so modifications inside the function only affect the local copy.
9. **Q: When should a structure be passed by value, by pointer, and by `const` pointer?**  
   **A:** By value for small read-only structs (`<= 16` B); by non-`const` pointer when the function must mutate the caller's object; by `const` pointer for read-only access to medium/large structs to avoid copying and prevent accidental writes.
10. **Q: What happens when you assign one structure variable to another (`b = a;`)?**  
    **A:** C performs a shallow member-wise copy of the entire structure (`sizeof(struct)` bytes).
11. **Q: How are elements of an array of structures laid out in memory?**  
    **A:** Contiguously in RAM, where element `i` starts at `base_address + i * sizeof(struct T)`.
12. **Q: Why is `char phone[10]` wrong for a 10-digit phone number in C?**  
    **A:** C strings require a trailing `'\0'` null terminator, so 10 digits need at least `char phone[11]`.

---

## Section B: Memory Layout, Padding, Alignment & Unions (10 Q&As)

13. **Q: What is structure alignment?**  
    **A:** The CPU requires data types (like 4-byte `int` or `float`) to be stored at memory addresses divisible by their alignment boundary (typically 4 bytes) for fast, fault-free access.
14. **Q: What is structure padding?**  
    **A:** Unused bytes inserted by the compiler between members (internal padding) or at the end of a struct (trailing padding) to satisfy alignment rules.
15. **Q: Why was `struct patient` 76 bytes instead of 75 bytes in Task 1?**  
    **A:** `char phone[11]` ends at offset 55, so the compiler inserts 1 padding byte before `struct blood_pressure` (which needs 4-byte alignment at offset 56).
16. **Q: Why must we never hardcode structure sizes instead of using `sizeof`?**  
    **A:** Padding, `enum` width, and pointer sizes (`4` B on 32-bit vs `8` B on 64-bit) depend on the compiler and target ABI.
17. **Q: How does a `union` differ from a `struct` in memory?**  
    **A:** A `struct` allocates separate memory for every member; a `union` overlays all members at the same starting address, with size equal to its largest member (rounded to strictest alignment).
18. **Q: What is a tagged union?**  
    **A:** A `struct` pairing an `enum` tag (recording which member is currently active) with a `union` holding the mutually exclusive payloads.
19. **Q: Why was `sizeof(struct reading)` 12 bytes and not 20 bytes in Task 3?**  
    **A:** `enum kind type` takes 4 bytes, and `union value` takes `max(4, 4, 8) = 8` bytes, totaling `4 + 8 = 12` bytes instead of `4 + 4 + 4 + 8 = 20` bytes.
20. **Q: What happened when we stored `31.5f` in `celsius` and read `percent` in Task 3.4?**  
    **A:** It printed `1107034112` (`0x41FC0000`), which is the raw IEEE-754 bit pattern of `31.5f` reinterpreted as an `int`.
21. **Q: Is reading an inactive union member a portable way to convert types in C?**  
    **A:** No. It depends on endianness, type sizes, and representation, and is not a portable type conversion.
22. **Q: Why is a tagged union better than `void *` heap packets for a memory-constrained weather station?**  
    **A:** A `void *` wrapper takes `16` bytes plus heap payload plus `malloc` metadata per packet and risks memory fragmentation, whereas a tagged union uses a fixed `12` bytes with zero heap overhead.

---

## Section C: Storage Classes & Argument Evaluation (10 Q&As)

23. **Q: What are the four storage classes in C?**  
    **A:** `auto`, `static`, `extern`, and `register`.
24. **Q: What is the difference between scope and lifetime?**  
    **A:** Scope is *where* in the source code an identifier is visible; lifetime is *how long* the variable exists in memory during execution.
25. **Q: Why does `auto_token()` always return `1001` while `next_token()` returns `1001, 1002, 1003`?**  
    **A:** An `auto` local variable is re-created and initialized to `1000` on every call; a `static` local variable is initialized once and persists for the entire program lifetime.
26. **Q: What is the default initial value of `auto` vs `static` variables?**  
    **A:** `auto` (and `register`) variables have indeterminate (garbage) initial values; `static` and global variables are zero-initialized by default.
27. **Q: How does `extern` share a variable across two `.c` files?**  
    **A:** One `.c` file holds the single definition (`int mess_token = 1000;`), while the other file uses `extern int mess_token;` to declare it without allocating duplicate storage.
28. **Q: What happens if you omit `extern` and write `int mess_token = 1000;` in both `.c` files?**  
    **A:** The linker fails with a "multiple definition" error.
29. **Q: Why is `&reg_var` (taking the address of a `register` variable) illegal in C?**  
    **A:** A `register` variable is a hint to store the value in a CPU register, which does not have a RAM memory address.
30. **Q: Why did `printf("%d %d %d", next_token(), next_token(), next_token())` print `1006 1005 1004`?**  
    **A:** C does not specify the evaluation order of function arguments. On x86_64 GCC, arguments were evaluated right-to-left.
31. **Q: Why is a caller-owned `int *counter` better than `static` for supporting Veg and Non-Veg counters?**  
    **A:** One function `next_token_ptr(int *counter)` works for any number of independent counters without duplicating functions or global state.
32. **Q: What is the risk of `extern` global variables in large programs?**  
    **A:** Any function in any linked file can accidentally modify the global variable, making debugging and unit testing harder.

---

## Section D: Data Modelling & Canteen Inventory Design (10 Q&As)

33. **Q: Why did we use a tagged union inside `struct CanteenItem`?**  
    **A:** An item is exclusively Packaged (expiry date), Cooked (prep time), or Combo (up to 3 component IDs), so a union saves memory while the `enum ItemType` tag guarantees safe access.
34. **Q: How does `Q6_Canteen_Main.c` prevent partial stock corruption when a combo sale fails?**  
    **A:** It uses a two-phase atomic check: Phase 1 verifies the combo's stock AND all component items' stock; Phase 2 deducts stock only if every check passes.
35. **Q: How is the 2-day expiry warning computed?**  
    **A:** Both the reference date and item expiry date are converted to integer serial day counts via `date_to_days()`, and items with `expiry_days - today_days <= 2` are flagged.
36. **Q: Why did `print_bill_summary()` sort a copy of the inventory rather than sorting `inventory[]` in place?**  
    **A:** Sorting a copy preserves the original inventory order (or index references) while displaying the daily bill sorted by revenue descending.
37. **Q: Why avoid global arrays in the canteen system?**  
    **A:** Passing `inventory[]` and `sales[]` via pointers makes functions self-contained, testable, and reusable.
38. **Q: What is the time complexity of `find_item()` in an array vs a singly linked list?**  
    **A:** Both are `O(n)` linear search when unsorted.
39. **Q: Is every linked-list insertion and deletion `O(1)`?**  
    **A:** No. Only insertion at the head (or after a known node pointer) is `O(1)`. Inserting or deleting by item ID requires `O(n)` traversal first.
40. **Q: How much extra memory did each linked-list node use in Task 6?**  
    **A:** `sizeof(struct ItemNode)` was `88` bytes vs `76` bytes for `struct CanteenItem` (`12` extra bytes: `8` B for `next` pointer + `4` B alignment padding, plus `malloc` metadata).
41. **Q: Why is an array of structures preferred over a linked list for a small college canteen?**  
    **A:** A canteen has a small, bounded menu (`< 100` items); arrays offer contiguous cache locality, zero `malloc`/`free` overhead, and simpler sorting.
42. **Q: How can we prevent invalid negative quantities or unknown item IDs?**  
    **A:** By validating `quantity > 0` and checking `find_item() != NULL` at the entry of `record_sale()` before any arithmetic or mutation.
