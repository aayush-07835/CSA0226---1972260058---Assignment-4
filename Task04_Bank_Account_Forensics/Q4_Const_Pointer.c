/*
 * Task 4 - Q4_Const_Pointer.c
 * Task 4.4: Demonstrates passing structures by value, by non-const pointer,
 * and by const pointer (read-only access without copying).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q4_Const_Pointer.c -o Q4_Const_Pointer
 * Run:     ./Q4_Const_Pointer
 */

#include <stdio.h>

struct account {
    int number;
    float balance;
};

/* Read-only access: const pointer avoids copying and prevents accidental writes */
void printAccount(const struct account *a) {
    if (a == NULL) return;
    /* a->balance = 0.0f;  <-- Would cause a compile-time error due to const! */
    printf("Account %d | Balance: Rs. %.2f\n", a->number, a->balance);
}

/* Mutating access: non-const pointer modifies the caller's object */
void applyInterest(struct account *a, float rate) {
    if (a == NULL) return;
    a->balance += a->balance * rate / 100.0f;
}

/* Small read-only value helper: pass by value */
float computeInterestAmount(struct account a, float rate) {
    return a.balance * rate / 100.0f;
}

int main(void) {
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};

    printf("=== Task 4.4 Const Pointer vs Pointer vs Value ===\n");
    for (int i = 0; i < 3; i++) {
        float interest = computeInterestAmount(list[i], 4.0f);
        printf("Projected 4%% interest for #%d: Rs. %.2f\n", list[i].number, interest);
        applyInterest(&list[i], 4.0f);
        printAccount(&list[i]);
    }
    return 0;
}
