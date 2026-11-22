/*
 * Task 1 - Q1_Repaired_Structure.c
 * Repaired Primary Health Centre Patient Register using nested structures,
 * structure pointers, input validation, capacity checks, and age sorting.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q1_Repaired_Structure.c -o Q1_Repaired_Structure
 * Run:     ./Q1_Repaired_Structure
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct date {
    int day;
    int month;
    int year;
};

struct blood_pressure {
    int systolic;
    int diastolic;
};

struct patient {
    char name[40];
    int age;
    char phone[11]; /* 10 digits + 1 null terminator */
    struct blood_pressure bp;
    struct date visitDate;
};

/* Validates that phone has exactly 10 numeric digits */
static int is_valid_phone(const char *phone) {
    if (phone == NULL || strlen(phone) != 10) {
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0;
        }
    }
    return 1;
}

/* Validates calendar date fields */
static int is_valid_date(const struct date *d) {
    if (d == NULL) return 0;
    if (d->year < 1900 || d->year > 2100) return 0;
    if (d->month < 1 || d->month > 12) return 0;
    if (d->day < 1 || d->day > 31) return 0;
    return 1;
}

/* Adds a patient via structure pointer with validation and capacity check */
int addPatient(struct patient list[], int *count, int capacity, const struct patient *p) {
    if (list == NULL || count == NULL || p == NULL) {
        return 0;
    }
    if (*count >= capacity) {
        printf("[ERROR] Register full (capacity %d). Cannot add %s.\n", capacity, p->name);
        return 0;
    }
    if (strlen(p->name) == 0) {
        printf("[ERROR] Patient name cannot be empty.\n");
        return 0;
    }
    if (p->age < 0 || p->age > 130) {
        printf("[ERROR] Invalid age (%d) for %s.\n", p->age, p->name);
        return 0;
    }
    if (!is_valid_phone(p->phone)) {
        printf("[ERROR] Invalid 10-digit phone (%s) for %s.\n", p->phone, p->name);
        return 0;
    }
    if (p->bp.systolic <= 0 || p->bp.diastolic <= 0 || p->bp.systolic < p->bp.diastolic) {
        printf("[ERROR] Invalid blood pressure (%d/%d) for %s.\n",
               p->bp.systolic, p->bp.diastolic, p->name);
        return 0;
    }
    if (!is_valid_date(&p->visitDate)) {
        printf("[ERROR] Invalid visit date for %s.\n", p->name);
        return 0;
    }

    list[*count] = *p;
    (*count)++;
    return 1;
}

void printPatient(const struct patient *p, int index) {
    printf("%-2d | %-20s | %3d | %-10s | %3d/%-3d mmHg | %02d/%02d/%04d\n",
           index + 1,
           p->name,
           p->age,
           p->phone,
           p->bp.systolic,
           p->bp.diastolic,
           p->visitDate.day,
           p->visitDate.month,
           p->visitDate.year);
}

/* Selection sort by ascending age; returns number of structure swaps */
int sortPatientsByAge(struct patient list[], int count) {
    int swaps = 0;
    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            if (list[j].age < list[min_idx].age) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct patient temp = list[i];
            list[i] = list[min_idx];
            list[min_idx] = temp;
            swaps++;
        }
    }
    return swaps;
}

int main(void) {
    struct patient register_list[MAX_PATIENTS];
    int count = 0;

    struct patient samples[5] = {
        {"Anitha Kumar", 42, "9876543210", {120, 80}, {12, 10, 2026}},
        {"Ramesh Babu", 67, "9123456789", {145, 95}, {13, 10, 2026}},
        {"Kavya Devi", 29, "9988776655", {112, 74}, {13, 10, 2026}},
        {"Suresh Nair", 54, "9445566778", {136, 88}, {14, 10, 2026}},
        {"Meena Iyer", 35, "9001122334", {118, 78}, {14, 10, 2026}}
    };

    printf("=== Q1 Repaired Structure-Based Patient Register ===\n");
    for (int i = 0; i < 5; i++) {
        addPatient(register_list, &count, MAX_PATIENTS, &samples[i]);
    }

    /* Boundary validation tests */
    struct patient invalid_phone = {"Test Invalid", 30, "12345", {120, 80}, {14, 10, 2026}};
    struct patient invalid_age = {"Test Age", 150, "9876543210", {120, 80}, {14, 10, 2026}};
    addPatient(register_list, &count, MAX_PATIENTS, &invalid_phone);
    addPatient(register_list, &count, MAX_PATIENTS, &invalid_age);

    printf("\n--- Registered Patients (Before Sorting) ---\n");
    for (int i = 0; i < count; i++) {
        printPatient(&register_list[i], i);
    }

    int swaps = sortPatientsByAge(register_list, count);

    printf("\n--- Registered Patients (Sorted by Age Ascending) ---\n");
    for (int i = 0; i < count; i++) {
        printPatient(&register_list[i], i);
    }

    printf("\n--- Memory Layout & Swap Measurements ---\n");
    printf("sizeof(struct date)           = %zu bytes\n", sizeof(struct date));
    printf("sizeof(struct blood_pressure) = %zu bytes\n", sizeof(struct blood_pressure));
    printf("sizeof(struct patient)        = %zu bytes\n", sizeof(struct patient));
    printf("Total register (100 slots)    = %zu bytes\n", sizeof(register_list));
    printf("Swaps performed               = %d\n", swaps);
    printf("Bytes copied per swap (3 assignments of struct patient) = %zu bytes\n",
           3 * sizeof(struct patient));

    return 0;
}
