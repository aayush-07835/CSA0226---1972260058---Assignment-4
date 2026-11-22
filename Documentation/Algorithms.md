# Algorithms — CSA02 CO4 Assignment 4

## Task 1: Patient Register (`addPatient` & `sortPatientsByAge`)
1. **Add Patient (`addPatient`):**
   - Step 1: Verify `list`, `count`, and `p` pointers are non-NULL and `*count < capacity`.
   - Step 2: Validate `name` (non-empty), `age` (`0..130`), `phone` (10 numeric digits), `bp` (`systolic > 0`, `diastolic > 0`, `systolic >= diastolic`), and `visitDate` (`day 1..31`, `month 1..12`, `year 1900..2100`).
   - Step 3: Copy `*p` into `list[*count]` and increment `(*count)++`.
2. **Sort Patients by Age:**
   - Use Selection Sort over indices `i = 0 .. count - 2`: find `min_idx` with minimum `list[j].age` in `i..count-1` and swap `list[i]` and `list[min_idx]`.

## Task 2: Courier Parcel Tracking (`sort_by_weight` & `list_parcels_by_city`)
1. **Sort Parcels by Weight:**
   - Selection Sort over `i = 0 .. n - 2`: locate `min_idx` with smallest `p[j].weight` and swap entire `struct parcel` (`44` bytes per assignment, `132` bytes per 3-step swap).
2. **List Parcels by Receiver City:**
   - Linearly scan `list[0..n-1]`, compare `list[i].receiver.addr.city` with target `city` using `strcmp`, and print matching records.

## Task 3: Weather-Station Sensor Packet (`show`)
1. Switch on `r->type`.
2. Case `TEMPERATURE`: print `r->value.celsius` (`%.1f C`).
3. Case `HUMIDITY`: print `r->value.percent` (`%d %`).
4. Case `STATUS`: print `r->value.status` (`%s`).

## Task 4: Bank Account Interest (`addInterest`)
1. Receive `struct account *a` and `float rate`.
2. Guard against `a == NULL` or `rate < 0`.
3. Update `a->balance = a->balance + a->balance * rate / 100.0f` in place.

## Task 5: Hostel Mess Token Counter
1. **Static Local:** `static int token = 1000; return ++token;` retains value across calls.
2. **Extern Global:** Single definition `int mess_token = 1000;` in `Q5_Extern_Counter.c`; declared `extern int mess_token;` in `Q5_Extern_Main.c`.
3. **Caller-Owned Pointer:** `int next_token_ptr(int *counter) { return ++(*counter); }` decouples state from function storage.

## Task 6: College Canteen Inventory & Billing
1. **Atomic Sale Recording (`record_sale`):**
   - Validate `quantity > 0` and locate `target = find_item(items, count, item_id)`.
   - If `target->type == ITEM_COMBO`, verify `target->stock >= quantity` AND every component `comp->stock >= quantity` *before* deducting any stock.
   - Deduct stocks, accumulate `units_sold` and `revenue`, and append `SaleRecord`.
2. **2-Day Expiry Check (`is_expiring_soon`):**
   - Convert `expiry` and `today` to serial day numbers via `date_to_days()`.
   - Flag packaged item if `expiry_days - today_days <= 2`.
3. **Revenue-Sorted Bill Summary:**
   - Copy inventory to `summary[]`, sort descending by `revenue` using Selection Sort, and print formatted daily bill.
