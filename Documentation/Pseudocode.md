# Pseudocode — SIMATS Engineering Standard for Algorithmic Pseudocode

## Task 2.3 (a) — Sort Parcels by Weight
```text
ALGORITHM SortParcelsByWeight(P, n)
INPUT:  P (array of Parcel structures), n (number of parcels)
OUTPUT: P sorted in ascending order of weight
BEGIN
    FOR i <- 0 TO n - 2 DO
        minIdx <- i
        FOR j <- i + 1 TO n - 1 DO
            IF P[j].weight < P[minIdx].weight THEN
                minIdx <- j
            ENDIF
        ENDFOR
        IF minIdx != i THEN
            temp <- P[i]
            P[i] <- P[minIdx]
            P[minIdx] <- temp
        ENDIF
    ENDFOR
END
```

## Task 2.3 (b) — List Parcels for a Given Receiver City
```text
ALGORITHM ListParcelsByCity(P, n, targetCity)
INPUT:  P (array of Parcel structures), n (count), targetCity (string)
OUTPUT: Printed list of matching parcels
BEGIN
    found <- FALSE
    FOR i <- 0 TO n - 1 DO
        IF P[i].receiver.addr.city = targetCity THEN
            PRINT P[i].id, P[i].weight, P[i].receiver.name, P[i].receiver.addr.pincode
            found <- TRUE
        ENDIF
    ENDFOR
    IF found = FALSE THEN
        PRINT "No parcels found for ", targetCity
    ENDIF
END
```

## Task 6 — Stage 4 Pseudocode

### 1. Record Sale (Atomic Stock Update)
```text
ALGORITHM RecordSale(items, itemCount, sales, saleCount, itemId, qty)
INPUT:  items (array of CanteenItem), itemCount, sales (array of SaleRecord),
        saleCount (reference), itemId, qty
OUTPUT: TRUE if sale succeeds, FALSE if rejected
BEGIN
    IF qty <= 0 THEN
        PRINT "Invalid quantity"
        RETURN FALSE
    ENDIF
    target <- FindItemById(items, itemCount, itemId)
    IF target = NULL THEN
        PRINT "Invalid Item ID"
        RETURN FALSE
    ENDIF
    IF target.type = ITEM_COMBO THEN
        IF target.stock < qty THEN
            RETURN FALSE
        ENDIF
        FOR k <- 0 TO target.details.combo.componentCount - 1 DO
            comp <- FindItemById(items, itemCount, target.details.combo.componentIds[k])
            IF comp = NULL OR comp.stock < qty THEN
                RETURN FALSE
            ENDIF
        ENDFOR
        target.stock <- target.stock - qty
        FOR k <- 0 TO target.details.combo.componentCount - 1 DO
            comp <- FindItemById(items, itemCount, target.details.combo.componentIds[k])
            comp.stock <- comp.stock - qty
        ENDFOR
    ELSE
        IF target.stock < qty THEN
            RETURN FALSE
        ENDIF
        target.stock <- target.stock - qty
    ENDIF
    amount <- target.price * qty
    target.unitsSold <- target.unitsSold + qty
    target.revenue <- target.revenue + amount
    AppendSaleRecord(sales, saleCount, itemId, qty, amount, SUCCESS)
    RETURN TRUE
END
```

### 2. Check Expiry (Within 2 Days)
```text
ALGORITHM CheckExpiryWarnings(items, itemCount, todayDate)
INPUT:  items (array of CanteenItem), itemCount, todayDate (Date)
OUTPUT: Prints warning for packaged items expiring within 2 days
BEGIN
    todayDays <- DateToSerialDays(todayDate)
    FOR i <- 0 TO itemCount - 1 DO
        IF items[i].type = ITEM_PACKAGED THEN
            expDays <- DateToSerialDays(items[i].details.packaged.expiry)
            diff <- expDays - todayDays
            IF diff <= 2 THEN
                PRINT "[WARN]", items[i].id, items[i].name, diff, "days left"
            ENDIF
        ENDIF
    ENDFOR
END
```

### 3. Generate & Sort Revenue Summary
```text
ALGORITHM GenerateSortedBillSummary(items, itemCount)
INPUT:  items (array of CanteenItem), itemCount
OUTPUT: Printed daily bill summary sorted by revenue descending
BEGIN
    COPY items[0..itemCount-1] INTO summary[0..itemCount-1]
    FOR i <- 0 TO itemCount - 2 DO
        maxIdx <- i
        FOR j <- i + 1 TO itemCount - 1 DO
            IF summary[j].revenue > summary[maxIdx].revenue THEN
                maxIdx <- j
            ENDIF
        ENDFOR
        IF maxIdx != i THEN
            SWAP summary[i], summary[maxIdx]
        ENDIF
    ENDFOR
    PRINT summary table and grand total revenue
END
```
