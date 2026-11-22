/*
 * Task 5 - Q5_Two_Independent_Counters.c
 * Task 5.2: Adapting all approaches to support two independent counters
 * (Vegetarian and Non-Vegetarian) without interference.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q5_Two_Independent_Counters.c -o Q5_Two_Independent_Counters
 * Run:     ./Q5_Two_Independent_Counters
 */

#include <stdio.h>

/* 1. Static local version: requires separate functions or a selector parameter */
int next_veg_static(void) {
    static int veg_token = 1000;
    return ++veg_token;
}

int next_nonveg_static(void) {
    static int nonveg_token = 2000;
    return ++nonveg_token;
}

/* 2. Global version: requires two separate global variables */
int g_veg_token = 1000;
int g_nonveg_token = 2000;

int next_veg_global(void) { return ++g_veg_token; }
int next_nonveg_global(void) { return ++g_nonveg_token; }

/* 3. Pointer-based alternative: single reusable function for ANY number of counters */
int next_token_ptr(int *counter) {
    return ++(*counter);
}

int main(void) {
    printf("=== Task 5.2 Two Independent Counters (Veg vs Non-Veg) ===\n");

    printf("\n[Static Local Version - 2 separate static variables/functions]\n");
    for (register int i = 0; i < 3; i++) {
        printf("Veg: %d | Non-Veg: %d\n", next_veg_static(), next_nonveg_static());
    }

    printf("\n[Global Version - 2 separate global variables]\n");
    for (register int i = 0; i < 3; i++) {
        printf("Veg: %d | Non-Veg: %d\n", next_veg_global(), next_nonveg_global());
    }

    printf("\n[Pointer Alternative - 1 reusable function, 0 global/static state]\n");
    int veg_counter = 1000;
    int nonveg_counter = 2000;
    for (register int i = 0; i < 3; i++) {
        printf("Veg: %d | Non-Veg: %d\n",
               next_token_ptr(&veg_counter), next_token_ptr(&nonveg_counter));
    }
    return 0;
}
