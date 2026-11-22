# Complexity Analysis — CSA02 CO4 Assignment 4

| Task | Primary Design | Alternative Design | Time Complexity | Space / Memory Comparison |
| :--- | :--- | :--- | :--- | :--- |
| **Task 1** | Array of Structures (`76` B/rec) | Parallel Arrays / SoA (`75` B/rec) | Sort: `O(n^2)` (both); AoS swaps 1 object vs 8 arrays | AoS: `7600` B (100 slots); SoA: `7504` B |
| **Task 2** | Nested Structures (`44` B / `140` B) | Flat Structure (`44` B) | Sort: `O(n^2)`, City filter: `O(n)` | Identical `44` B in `Q2_Parcel_Tracking`; nested enables reuse |
| **Task 3** | Tagged Union (`12` B/pkt) | Normal Struct (`20` B) / `void*` (`16` B + heap) | Packet read: `O(1)` (tagged union & struct) | Tagged union saves `8` B/pkt (`40%`) over normal struct |
| **Task 4** | Pointer Pass (`struct account *`) | Value + Return Struct | Update: `O(1)` per account (`O(n)` total) | Pointer copies `8` B address; value+return copies `16` B (`2x8` B) |
| **Task 5** | `static` / `extern` / `auto` / `register` | Caller-owned `int *counter` | Token issue: `O(1)` in all cases | `4` B per counter; pointer allows `k` independent counters with `1` function |
| **Task 6** | Array of Structures (`76` B/item) | Singly Linked List (`88` B/node) | Head insert: `O(1)` list vs `O(1)` append; Search/Delete: `O(n)` both | List adds `12` B/node (`8` B pointer + `4` B align pad) + `malloc` overhead |

## Key Engineering Takeaways
1. **Task 1 (AoS vs SoA):** AoS simplifies sorting (`3` assignments = `228` B) and function passing; SoA is only preferable in SIMD/columnar analytics where a single field is scanned across thousands of records.
2. **Task 4 (Pointer vs Value):** For small 8-byte structs, register-level pass-by-value is competitive; pointers become clearly superior when mutating in place or when structs grow large (`> 16–32` bytes).
3. **Task 6 (Array vs Linked List):** Only head insertion (`O(1)`) or deletion *given a predecessor pointer* is `O(1)` in a linked list; searching by ID or deleting by ID still requires `O(n)` traversal. For a small college canteen (`< 100` items), an array of structures provides better cache locality and zero `malloc` fragmentation.
