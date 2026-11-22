/*
 * Task 5 - Q5_Register_Loop.c
 * Demonstrates register storage class for a loop counter variable.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q5_Register_Loop.c -o Q5_Register_Loop
 * Run:     ./Q5_Register_Loop
 */

#include <stdio.h>

static int next_mess_token(void) {
    static int token = 1000;
    return ++token;
}

int main(void) {
    printf("=== Task 5.1 (d) Register Loop Variable ===\n");
    /* 'register' hints to the compiler to keep 'i' in a CPU register.
       Taking &i is forbidden in standard C because registers have no memory address. */
    for (register int i = 1; i <= 5; i++) {
        printf("Student %d -> Token: %d\n", i, next_mess_token());
    }
    return 0;
}
