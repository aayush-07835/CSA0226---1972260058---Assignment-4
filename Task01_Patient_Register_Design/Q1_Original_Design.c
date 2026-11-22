/*
 * Task 1 - Q1_Original_Design.c
 * Demonstrates the original flawed parallel-array patient register design
 * from the Primary Health Centre problem (for diagnostic comparison).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q1_Original_Design.c -o Q1_Original_Design
 * Run:     ./Q1_Original_Design
 */

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

/* Flaw 6: Global parallel arrays expose state to any function */
char name[MAX_PATIENTS][20];
int age[MAX_PATIENTS];
char phone[MAX_PATIENTS][10];     /* Flaw 2: Too small for 10 digits + '\0' */
float bp[MAX_PATIENTS];           /* Flaw 3: Cannot store systolic/diastolic */
char visitDate[MAX_PATIENTS][8];  /* Flaw 4: "DD/MM/YY" is 8 chars, no room for '\0' */
int count = 0;

void addPatient(const char n[], int a, const char p[], float b, const char d[]) {
    /* Flaw 5: No bounds check on count in original design (guarded here only to prevent UB) */
    if (count >= MAX_PATIENTS) {
        printf("[WARN] Capacity exceeded! Original design lacked this check.\n");
        return;
    }
    /* Using bounded copy here to prevent crash while showing truncation */
    strncpy(name[count], n, 19);
    name[count][19] = '\0';

    age[count] = a;

    /* Flaw 2 demonstration: 10-digit phone gets truncated to 9 chars + '\0' */
    strncpy(phone[count], p, 9);
    phone[count][9] = '\0';

    bp[count] = b;

    /* Flaw 4 demonstration: "12/10/26" (8 chars) loses null terminator if 8 bytes */
    strncpy(visitDate[count], d, 7);
    visitDate[count][7] = '\0';

    count++;
}

int main(void) {
    printf("=== Q1 Original Parallel-Array Design (Diagnostic Demo) ===\n");
    addPatient("Anitha Kumar", 42, "9876543210", 120.80f, "12/10/26");
    addPatient("Ramesh Babu", 67, "9123456789", 145.95f, "13/10/26");

    for (int i = 0; i < count; i++) {
        printf("Patient %d: Name=%s | Age=%d | Phone(truncated)=%s | BP(ambiguous)=%.2f | Date(truncated)=%s\n",
               i + 1, name[i], age[i], phone[i], bp[i], visitDate[i]);
    }

    size_t total_bytes = sizeof(name) + sizeof(age) + sizeof(phone) + sizeof(bp) + sizeof(visitDate) + sizeof(count);
    printf("Total global parallel-array footprint (100 slots): %zu bytes\n", total_bytes);
    return 0;
}
