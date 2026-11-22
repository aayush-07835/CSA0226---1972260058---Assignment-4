/*
 * Task 4 - Q4_Pointer_Repair.c
 * Task 4.3: Repaired Bank Account Interest Program using structure pointers
 * and the arrow (->) operator.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q4_Pointer_Repair.c -o Q4_Pointer_Repair
 * Run:     ./Q4_Pointer_Repair
 */

#include <stdio.h>

struct account {
    int number;
    float balance;
};

void addInterest(struct account *a, float rate) {
    if (a == NULL || rate < 0.0f) {
        return;
    }
    printf("  Inside addInterest(): a = %p -> modifying original object\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100.0f;
}

int main(void) {
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};
    struct account *p = list;

    printf("=== Task 4.3 Repaired Program (4%% Interest via Pointer) ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Before: &list[%d] = %p | Account %d | Balance = %.2f\n",
               i, (void *)&list[i], list[i].number, list[i].balance);
        addInterest(&list[i], 4.0f);
    }

    printf("\n--- Updated Account Balances (Accessed via Pointer p) ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Account %d: %.2f\n", (p + i)->number, (p + i)->balance);
    }
    return 0;
}
