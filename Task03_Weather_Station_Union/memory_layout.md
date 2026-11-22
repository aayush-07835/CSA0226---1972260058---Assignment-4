# Task 3 — Weather-Station Packet Memory Layout

## 1. Tagged Union (`struct reading` — Verified 12 Bytes on x86_64 GCC 12.2)

```text
Offset   0   1   2   3   4   5   6   7   8   9  10  11
       +---------------+-------------------------------+
       |  enum kind    |        union value (8 B)      |
       |    type (4B)  | float celsius (4B) + 4B pad   |
       |               | int percent   (4B) + 4B pad   |
       |               | char status[8] (8B)           |
       +---------------+-------------------------------+
Total = 4 + 8 = 12 bytes (4-byte alignment, 0 external padding)
```

- **Why 12 bytes and not 4 + 4 + 4 + 8 (20 bytes)?**  
  Because a `union` overlays all its members at the same starting offset (offset `4`). Its size is `max(4, 4, 8) = 8` bytes, aligned to `4` bytes (`max(align(float)=4, align(int)=4, align(char)=1)`). Adding the `4`-byte `enum kind type` gives `4 + 8 = 12` bytes.

## 2. Normal Structure (`struct reading_struct` — Verified 20 Bytes)

```text
Offset   0..3        4..7        8..11       12..19
       +-----------+-----------+-----------+-------------------+
       | type (4B) | celsius   | percent   |   status[8] (8B)  |
       +-----------+-----------+-----------+-------------------+
Total = 4 + 4 + 4 + 8 = 20 bytes
```

## 3. Platform Dependence Note
The C11 standard does not fix the size of `enum` (commonly 4 bytes on LP64 x86_64/ARM64, but could be smaller on some embedded ABIs with `-fshort-enums`). Always use `sizeof` rather than hardcoding byte counts.
