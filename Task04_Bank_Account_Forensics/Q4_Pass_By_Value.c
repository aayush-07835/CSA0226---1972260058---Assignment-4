/*
 * Task 4 - Q4_Pass_By_Value.c
 * Task 4.2: Address evidence proving pass-by-value creates a distinct copy on the stack.
 * Also implements the Alternative Concept (returning modified struct by value).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q4_Pass_By_Value.c -o Q4_Pass_By_Value
 * Run:     ./Q4_Pass_By_Value
 */

#include <stdio.h>

struct account {
    int number;
    float balance;
};

/* Defect 1 evidence: 'a' is a copy at a different stack address */
void addInterest_by_value_void(struct account a, float rate) {
    printf("  Inside addInterest_by_value_void: &a = %p (Account %d)\n",
           (void *)&a, a.number);
    a.balance = a.balance + a.balance * rate / 100.0f;
}

/* Alternative concept: pass by value and return modified copy */
struct account addInterest_return_value(struct account a, float rate) {
    a.balance = a.balance + a.balance * rate / 100.0f;
    return a;
}

int main(void) {
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};

    printf("=== Task 4.2 Address Evidence (Pass-by-Value vs Original) ===\n");
    for (int i = 0; i < 3; i++) {
        printf("In main(): &list[%d] = %p (Account %d, Balance=%.2f)\n",
               i, (void *)&list[i], list[i].number, list[i].balance);
        addInterest_by_value_void(list[i], 4.0f);
        printf("  After void call: list[%d].balance = %.2f (UNCHANGED)\n",
               i, list[i].balance);
    }

    printf("\n=== Alternative Concept: Return Modified Struct by Value ===\n");
    for (int i = 0; i < 3; i++) {
        list[i] = addInterest_return_value(list[i], 4.0f);
        printf("Account %d updated balance: %.2f\n", list[i].number, list[i].balance);
    }

    printf("\nsizeof(struct account)   = %zu bytes\n", sizeof(struct account));
    printf("sizeof(struct account *) = %zu bytes\n", sizeof(struct account *));
    return 0;
}
