/*
 * Task 1 - Q1_Parallel_Arrays.c
 * Alternative Concept: Repaired Parallel Arrays (Structure of Arrays)
 * with proper sizes and bounds checking, to compare sorting effort and memory
 * against the Array of Structures design.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q1_Parallel_Arrays.c -o Q1_Parallel_Arrays
 * Run:     ./Q1_Parallel_Arrays
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct parallel_register {
    char name[MAX_PATIENTS][40];
    int age[MAX_PATIENTS];
    char phone[MAX_PATIENTS][11];
    int systolic[MAX_PATIENTS];
    int diastolic[MAX_PATIENTS];
    int day[MAX_PATIENTS];
    int month[MAX_PATIENTS];
    int year[MAX_PATIENTS];
    int count;
};

static void swap_int(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void swap_str(char *a, char *b, size_t size) {
    char tmp[64];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

int sort_parallel_by_age(struct parallel_register *reg) {
    int swaps = 0;
    for (int i = 0; i < reg->count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < reg->count; j++) {
            if (reg->age[j] < reg->age[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            /* Must manually swap all 8 parallel arrays in lockstep */
            swap_str(reg->name[i], reg->name[min_idx], 40);
            swap_int(&reg->age[i], &reg->age[min_idx]);
            swap_str(reg->phone[i], reg->phone[min_idx], 11);
            swap_int(&reg->systolic[i], &reg->systolic[min_idx]);
            swap_int(&reg->diastolic[i], &reg->diastolic[min_idx]);
            swap_int(&reg->day[i], &reg->day[min_idx]);
            swap_int(&reg->month[i], &reg->month[min_idx]);
            swap_int(&reg->year[i], &reg->year[min_idx]);
            swaps++;
        }
    }
    return swaps;
}

int main(void) {
    struct parallel_register reg = {0};

    const char *names[5] = {"Anitha Kumar", "Ramesh Babu", "Kavya Devi", "Suresh Nair", "Meena Iyer"};
    int ages[5] = {42, 67, 29, 54, 35};
    const char *phones[5] = {"9876543210", "9123456789", "9988776655", "9445566778", "9001122334"};
    int sys[5] = {120, 145, 112, 136, 118};
    int dia[5] = {80, 95, 74, 88, 78};
    int d[5] = {12, 13, 13, 14, 14};
    int m[5] = {10, 10, 10, 10, 10};
    int y[5] = {2026, 2026, 2026, 2026, 2026};

    for (int i = 0; i < 5; i++) {
        strcpy(reg.name[i], names[i]);
        reg.age[i] = ages[i];
        strcpy(reg.phone[i], phones[i]);
        reg.systolic[i] = sys[i];
        reg.diastolic[i] = dia[i];
        reg.day[i] = d[i];
        reg.month[i] = m[i];
        reg.year[i] = y[i];
        reg.count++;
    }

    int swaps = sort_parallel_by_age(&reg);
    printf("=== Q1 Repaired Parallel Arrays (SoA) ===\n");
    for (int i = 0; i < reg.count; i++) {
        printf("%-2d | %-20s | %3d | %-10s | %3d/%-3d mmHg | %02d/%02d/%04d\n",
               i + 1, reg.name[i], reg.age[i], reg.phone[i],
               reg.systolic[i], reg.diastolic[i], reg.day[i], reg.month[i], reg.year[i]);
    }

    printf("\nTotal parallel_register footprint (100 slots): %zu bytes\n", sizeof(reg));
    printf("Swaps performed: %d (8 separate array swaps per logical patient swap)\n", swaps);
    return 0;
}
