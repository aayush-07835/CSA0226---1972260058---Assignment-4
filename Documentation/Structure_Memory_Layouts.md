# Structure Memory Layouts & Alignment Analysis

All actual measurements below were obtained on **x86_64 Linux** using **GCC 12.2.0** (`-std=c11 -Wall -Wextra -pedantic`). Theoretical predictions follow System V AMD64 ABI alignment rules (`char`: 1B, `int`: 4B, `float`: 4B, pointers: 8B, `enum`: 4B).

---

## 1. Patient Structure (`Q1_Repaired_Structure.c`)
- `struct date`: `int day (4B) + int month (4B) + int year (4B)` -> **12 bytes** (align 4, 0 padding).
- `struct blood_pressure`: `int systolic (4B) + int diastolic (4B)` -> **8 bytes** (align 4, 0 padding).
- `struct patient`:
  - `char name[40]` (offset `0..39`, 40B)
  - `int age` (offset `40..43`, 4B)
  - `char phone[11]` (offset `44..54`, 11B)
  - **1 byte internal padding** (offset `55`) to align `struct bp` on 4-byte boundary!
  - `struct blood_pressure bp` (offset `56..63`, 8B)
  - `struct date visitDate` (offset `64..75`, 12B)
  - **Predicted = Verified `sizeof(struct patient)` = 76 bytes** (100 slots = `7600` B).

## 2. Courier Parcel Structure (`Q2_Parcel_Tracking.c` & `Q2_Nested_Structure.c`)
- `struct parcel` (`Q2_Parcel_Tracking.c`):
  - `int id` (4B, offset `0..3`)
  - `float weight` (4B, offset `4..7`)
  - `struct address to` (`char city[20]` + `int pincode` = 24B, offset `8..31`)
  - `struct date booked` (`3 * int` = 12B, offset `32..43`)
  - **Predicted = Verified `sizeof(struct parcel)` = 44 bytes** (0 padding).
- Full `Parcel` (`Q2_Nested_Structure.c`): `4 + 4 + 12 + 56 + 56 + 4 + 4` = **140 bytes** (verified).

## 3. Weather-Station Packet (`Q3_Tagged_Union.c` vs `Q3_Structure_Design.c`)
- `struct reading` (Tagged Union):
  - `enum kind type` (4B, offset `0..3`)
  - `union value` (`max(4, 4, 8) = 8B`, align `4`, offset `4..11`)
  - **Predicted = Verified `sizeof(union)` = 8 bytes, `sizeof(struct reading)` = 12 bytes**.
- `struct reading_struct` (Normal Struct): `4 + 4 + 4 + 8` = **20 bytes** (verified).

## 4. Bank Account Structure (`Q4_Pointer_Repair.c`)
- `struct account`: `int number` (4B, offset `0..3`) + `float balance` (4B, offset `4..7`) = **8 bytes** (verified).
- `sizeof(struct account *)` = **8 bytes** on 64-bit x86_64 (verified).

## 5. Canteen Item with Tagged Union (`Q6_Canteen_Main.c`)
- `struct CanteenItem`:
  - `int id` (4B, `0..3`)
  - `char name[36]` (36B, `4..39`)
  - `float price` (4B, `40..43`)
  - `int stock` (4B, `44..47`)
  - `enum ItemType type` (4B, `48..51`)
  - `union details` (`ComboInfo` is largest: `int[3] + int` = 16B, `52..67`)
  - `int units_sold` (4B, `68..71`)
  - `float revenue` (4B, `72..75`)
  - **Predicted = Verified `sizeof(struct CanteenItem)` = 76 bytes**.
- Linked List node (`Q6_Alternative_Linked_List.c`) adds `struct ItemNode *next` (8B, align 8):
  - `76` bytes + **4 bytes padding** before 8-byte pointer + `8` bytes pointer = **88 bytes** (verified).

## 6. Array of Structures & Pointer Access
- Elements of `struct T arr[N]` sit contiguously at `base + i * sizeof(struct T)`.
- Pointer arithmetic `(p + i)->member` scales `i` by `sizeof(*p)` automatically (`&list[0] = 0x...10`, `&list[1] = 0x...18`, `&list[2] = 0x...20` — 8-byte stride in Task 4).

## 7. Structure Padding & Alignment Summary
- Every member sits at an offset divisible by its natural alignment.
- Total structure size is rounded up to a multiple of its strictest member alignment.
- Theoretical predictions matched GCC 12.2.0 measurements across all 6 tasks, though `enum` width and padding can vary across 32-bit/embedded ABIs, so `sizeof` must always be queried at compile time.
