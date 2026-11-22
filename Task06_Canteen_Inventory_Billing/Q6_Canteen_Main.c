/*
 * Task 6 - Q6_Canteen_Main.c
 * College Canteen Inventory and Billing System (Design Challenge - 13 Marks)
 * Uses nested structures, enums, tagged union, arrays of structures,
 * structure pointers, atomic combo stock updates, 2-day expiry check,
 * and revenue-sorted daily bill summary.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q6_Canteen_Main.c -o Q6_Canteen_Main
 * Run:     ./Q6_Canteen_Main
 */

#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_SALES 200

struct Date {
    int day;
    int month;
    int year;
};

struct Time {
    int hour;
    int minute;
};

enum ItemType {
    ITEM_PACKAGED = 0,
    ITEM_COOKED   = 1,
    ITEM_COMBO    = 2
};

struct PackagedInfo {
    struct Date expiry;
};

struct CookedInfo {
    struct Time prep_time;
};

struct ComboInfo {
    int component_ids[3];
    int component_count;
};

struct CanteenItem {
    int id;
    char name[36];
    float price;
    int stock;
    enum ItemType type;
    union {
        struct PackagedInfo packaged;
        struct CookedInfo cooked;
        struct ComboInfo combo;
    } details;
    int units_sold;
    float revenue;
};

struct SaleRecord {
    int sale_id;
    int item_id;
    int quantity;
    float total_amount;
    int status; /* 1 = Success, 0 = Rejected */
};

/* Helper: converts date to serial day count (Howard Hinnant civil-from-days algorithm) */
static long date_to_days(const struct Date *d) {
    int y = d->year;
    int m = d->month;
    int day = d->day;
    y -= (m <= 2);
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = (unsigned)(y - era * 400);
    const unsigned doy = (153 * (unsigned)(m + (m > 2 ? -3 : 9)) + 2) / 5 + (unsigned)day - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return (long)era * 146097L + (long)doe - 719468L;
}

/* Finds item by ID using structure pointers; returns NULL if not found */
struct CanteenItem *find_item(struct CanteenItem items[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (items[i].id == id) {
            return &items[i];
        }
    }
    return NULL;
}

/* Checks if a packaged item expires within 2 days (0..2 days inclusive, or already expired) */
int is_expiring_soon(const struct CanteenItem *item, const struct Date *today, long *days_left) {
    if (item == NULL || item->type != ITEM_PACKAGED) {
        return 0;
    }
    long diff = date_to_days(&item->details.packaged.expiry) - date_to_days(today);
    if (days_left != NULL) {
        *days_left = diff;
    }
    return (diff <= 2);
}

void print_expiry_warnings(const struct CanteenItem items[], int count, const struct Date *today) {
    printf("\n=== Expiry Warning Report (Reference Date: %02d/%02d/%04d) ===\n",
           today->day, today->month, today->year);
    int warnings = 0;
    for (int i = 0; i < count; i++) {
        if (items[i].type == ITEM_PACKAGED) {
            long days_left = 0;
            if (is_expiring_soon(&items[i], today, &days_left)) {
                printf("[WARN] ID %d (%s) expires on %02d/%02d/%04d (%ld day(s) left) | Stock: %d\n",
                       items[i].id, items[i].name,
                       items[i].details.packaged.expiry.day,
                       items[i].details.packaged.expiry.month,
                       items[i].details.packaged.expiry.year,
                       days_left, items[i].stock);
                warnings++;
            } else {
                printf("[OK]   ID %d (%s) expires on %02d/%02d/%04d (%ld day(s) left)\n",
                       items[i].id, items[i].name,
                       items[i].details.packaged.expiry.day,
                       items[i].details.packaged.expiry.month,
                       items[i].details.packaged.expiry.year,
                       days_left);
            }
        }
    }
    if (warnings == 0) {
        printf("No packaged items expiring within 2 days.\n");
    }
}

/* Records a sale atomically: validates ID, quantity, and all component stock before updating */
int record_sale(struct CanteenItem items[], int item_count,
                struct SaleRecord sales[], int *sale_count,
                int item_id, int quantity) {
    if (*sale_count >= MAX_SALES) {
        printf("[REJECTED] Sale log capacity reached.\n");
        return 0;
    }

    int sid = *sale_count + 1;
    if (quantity <= 0) {
        printf("[REJECTED] Sale #%d: Invalid quantity (%d) for Item ID %d.\n",
               sid, quantity, item_id);
        sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, 0.0f, 0};
        return 0;
    }

    struct CanteenItem *target = find_item(items, item_count, item_id);
    if (target == NULL) {
        printf("[REJECTED] Sale #%d: Invalid Item ID %d.\n", sid, item_id);
        sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, 0.0f, 0};
        return 0;
    }

    if (target->type == ITEM_COMBO) {
        /* Phase 1: Validate combo stock AND all component items' stock before mutating */
        if (target->stock < quantity) {
            printf("[REJECTED] Sale #%d: Combo '%s' stock (%d) < requested (%d).\n",
                   sid, target->name, target->stock, quantity);
            sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, 0.0f, 0};
            return 0;
        }
        for (int c = 0; c < target->details.combo.component_count; c++) {
            int comp_id = target->details.combo.component_ids[c];
            struct CanteenItem *comp = find_item(items, item_count, comp_id);
            if (comp == NULL || comp->stock < quantity) {
                printf("[REJECTED] Sale #%d: Combo '%s' blocked — component ID %d (%s) has insufficient stock (%d < %d).\n",
                       sid, target->name, comp_id, comp ? comp->name : "Unknown",
                       comp ? comp->stock : 0, quantity);
                sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, 0.0f, 0};
                return 0;
            }
        }
        /* Phase 2: All checks passed -> deduct combo and component stocks atomically */
        target->stock -= quantity;
        for (int c = 0; c < target->details.combo.component_count; c++) {
            struct CanteenItem *comp = find_item(items, item_count,
                                                 target->details.combo.component_ids[c]);
            comp->stock -= quantity;
        }
    } else {
        if (target->stock < quantity) {
            printf("[REJECTED] Sale #%d: '%s' stock (%d) < requested (%d).\n",
                   sid, target->name, target->stock, quantity);
            sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, 0.0f, 0};
            return 0;
        }
        target->stock -= quantity;
    }

    float amount = target->price * (float)quantity;
    target->units_sold += quantity;
    target->revenue += amount;
    sales[(*sale_count)++] = (struct SaleRecord){sid, item_id, quantity, amount, 1};

    printf("[SUCCESS]  Sale #%d: %d x %-22s @ Rs.%6.2f = Rs.%7.2f (Remaining stock: %d)\n",
           sid, quantity, target->name, target->price, amount, target->stock);
    return 1;
}

/* Sorts items in descending order of revenue (selection sort on summary copy) */
void sort_by_revenue_desc(struct CanteenItem summary[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (summary[j].revenue > summary[max_idx].revenue) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            struct CanteenItem tmp = summary[i];
            summary[i] = summary[max_idx];
            summary[max_idx] = tmp;
        }
    }
}

void print_bill_summary(const struct CanteenItem items[], int count) {
    struct CanteenItem summary[MAX_ITEMS];
    for (int i = 0; i < count; i++) {
        summary[i] = items[i];
    }
    sort_by_revenue_desc(summary, count);

    printf("\n=== Daily Bill Summary (Sorted by Revenue Descending) ===\n");
    printf("%-4s | %-24s | %-8s | %5s | %6s | %10s\n",
           "ID", "Item Name", "Type", "Sold", "Stock", "Revenue");
    printf("-----+--------------------------+----------+-------+--------+-----------\n");
    float grand_total = 0.0f;
    for (int i = 0; i < count; i++) {
        const char *type_str = (summary[i].type == ITEM_PACKAGED) ? "Packaged" :
                               (summary[i].type == ITEM_COOKED)   ? "Cooked"   : "Combo";
        printf("%-4d | %-24s | %-8s | %5d | %6d | Rs.%7.2f\n",
               summary[i].id, summary[i].name, type_str,
               summary[i].units_sold, summary[i].stock, summary[i].revenue);
        grand_total += summary[i].revenue;
    }
    printf("-----+--------------------------+----------+-------+--------+-----------\n");
    printf("Total Daily Revenue: Rs. %.2f\n", grand_total);
}

int main(void) {
    struct Date today = {12, 10, 2026};

    struct CanteenItem inventory[MAX_ITEMS] = {
        {101, "Mango Juice 250ml",   35.0f, 15, ITEM_PACKAGED, {.packaged = {{13, 10, 2026}}}, 0, 0.0f},
        {102, "Biscuit Pack",        20.0f, 25, ITEM_PACKAGED, {.packaged = {{25, 10, 2026}}}, 0, 0.0f},
        {103, "Masala Dosa",         50.0f, 12, ITEM_COOKED,   {.cooked   = {{8, 30}}},        0, 0.0f},
        {104, "Veg Fried Rice",      75.0f,  4, ITEM_COOKED,   {.cooked   = {{11, 45}}},       0, 0.0f},
        {201, "Lunch Combo Meal",   100.0f, 10, ITEM_COMBO,    {.combo    = {{104, 101, 0}, 2}}, 0, 0.0f},
        {202, "Tiffin Combo Meal",   80.0f,  8, ITEM_COMBO,    {.combo    = {{103, 101, 102}, 3}}, 0, 0.0f}
    };
    int item_count = 6;

    struct SaleRecord sales[MAX_SALES];
    int sale_count = 0;

    printf("=== College Canteen Inventory & Billing System ===\n");
    /* Test Cases 5 & 6: Expiring within 2 days vs not expiring within 2 days */
    print_expiry_warnings(inventory, item_count, &today);

    printf("\n=== Processing Sales Transactions ===\n");
    /* Test Case 1: Normal sale of a packaged item */
    record_sale(inventory, item_count, sales, &sale_count, 102, 4);
    /* Test Case 2: Normal sale of a cooked item */
    record_sale(inventory, item_count, sales, &sale_count, 103, 3);
    /* Test Case 3: Sale of a combo meal (3 components: 103, 101, 102) */
    record_sale(inventory, item_count, sales, &sale_count, 202, 2);
    /* Test Case 9: Multiple sales of the same item */
    record_sale(inventory, item_count, sales, &sale_count, 102, 3);
    /* Test Case 4a: Sale exceeding available stock (cooked item 104 has stock 4) */
    record_sale(inventory, item_count, sales, &sale_count, 104, 10);
    /* Test Case 4b: Combo sale blocked because component 104 only has stock 4 */
    record_sale(inventory, item_count, sales, &sale_count, 201, 6);
    /* Test Case 10a: Invalid item ID */
    record_sale(inventory, item_count, sales, &sale_count, 999, 1);
    /* Test Case 10b: Invalid quantity */
    record_sale(inventory, item_count, sales, &sale_count, 101, -2);

    /* Test Cases 7 & 8: Updated inventory & daily bill summary sorted by revenue */
    print_bill_summary(inventory, item_count);

    printf("\n=== Structure Memory Sizes ===\n");
    printf("sizeof(struct Date)        = %zu bytes\n", sizeof(struct Date));
    printf("sizeof(struct Time)        = %zu bytes\n", sizeof(struct Time));
    printf("sizeof(struct CanteenItem) = %zu bytes\n", sizeof(struct CanteenItem));
    printf("sizeof(struct SaleRecord)  = %zu bytes\n", sizeof(struct SaleRecord));
    return 0;
}
