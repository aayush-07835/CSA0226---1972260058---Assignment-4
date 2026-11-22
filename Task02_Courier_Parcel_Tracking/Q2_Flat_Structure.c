/*
 * Task 2 - Q2_Flat_Structure.c
 * Alternative Concept: Flat Parcel structure without nested Date or Address structures,
 * for comparing access paths, reuse, and sizeof against nested structures.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q2_Flat_Structure.c -o Q2_Flat_Structure
 * Run:     ./Q2_Flat_Structure
 */

#include <stdio.h>

struct parcel_flat {
    int id;
    float weight;
    char to_city[20];
    int to_pincode;
    int booked_day;
    int booked_month;
    int booked_year;
};

void print_parcel_flat(const struct parcel_flat *p) {
    printf("%d  %.1f kg  %s-%d  %02d/%02d/%04d\n",
           p->id, p->weight, p->to_city, p->to_pincode,
           p->booked_day, p->booked_month, p->booked_year);
}

void sort_by_weight_flat(struct parcel_flat p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (p[j].weight < p[min_idx].weight) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct parcel_flat temp = p[i];
            p[i] = p[min_idx];
            p[min_idx] = temp;
        }
    }
}

int main(void) {
    struct parcel_flat list[3] = {
        {501, 4.5f, "Madurai", 625001, 12, 10, 2026},
        {502, 1.2f, "Chennai", 600077, 12, 10, 2026},
        {503, 2.8f, "Coimbatore", 641001, 13, 10, 2026}
    };

    sort_by_weight_flat(list, 3);
    printf("=== Flat Structure Parcel List ===\n");
    for (int i = 0; i < 3; i++) {
        print_parcel_flat(&list[i]);
    }
    printf("sizeof(struct parcel_flat) = %zu bytes\n", sizeof(struct parcel_flat));
    return 0;
}
