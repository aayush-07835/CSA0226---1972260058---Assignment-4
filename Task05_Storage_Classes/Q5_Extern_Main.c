/*
 * Task 5 - Q5_Extern_Main.c
 * First translation unit declaring extern mess_token and calling next_extern_token().
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q5_Extern_Main.c Q5_Extern_Counter.c -o Q5_Extern_Counter
 * Run:     ./Q5_Extern_Counter
 */

#include <stdio.h>

extern int mess_token;          /* Declaration (no storage allocated here) */
int next_extern_token(void);    /* Function prototype from Q5_Extern_Counter.c */

int main(void) {
    printf("=== Task 5.1 (c) Global Variable Shared via extern ===\n");
    printf("Initial mess_token (from Q5_Extern_Counter.c): %d\n", mess_token);
    printf("extern tokens: %d %d %d\n",
           next_extern_token(), next_extern_token(), next_extern_token());
    printf("Final mess_token in main: %d\n", mess_token);
    return 0;
}
