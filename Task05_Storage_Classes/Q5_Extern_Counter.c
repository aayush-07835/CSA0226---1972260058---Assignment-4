/*
 * Task 5 - Q5_Extern_Counter.c
 * Second translation unit defining the single global variable shared via extern.
 *
 * Compile with main:
 *   gcc -std=c11 -Wall -Wextra -pedantic Q5_Extern_Main.c Q5_Extern_Counter.c -o Q5_Extern_Counter
 * Run:
 *   ./Q5_Extern_Counter
 */

int mess_token = 1000; /* Single external definition */

int next_extern_token(void) {
    return ++mess_token;
}
