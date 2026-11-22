/*
 * Task 5 - Q5_Auto_Counter.c
 * Demonstrates automatic storage class (auto) for a local counter variable.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q5_Auto_Counter.c -o Q5_Auto_Counter
 * Run:     ./Q5_Auto_Counter
 */

#include <stdio.h>

int next_auto_token(void) {
    auto int token = 1000; /* 'auto' is the default for local variables */
    return ++token;
}

int main(void) {
    printf("=== Task 5.1 (a) Automatic Local Variable ===\n");
    for (int i = 0; i < 4; i++) {
        printf("Call %d -> Token: %d\n", i + 1, next_auto_token());
    }
    return 0;
}
