/*
 * Task 5 - Q5_Static_Counter.c
 * Exact supplied "Complete the Code" program with TODO 1 completed,
 * plus the single-printf evaluation order experiment and pointer-based alternative.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q5_Static_Counter.c -o Q5_Static_Counter
 * Run:     ./Q5_Static_Counter
 */

#include <stdio.h>

/* Issues the next mess token number, starting from 1001. */
int next_token(void)
{
    /* TODO 1: Use a static local variable so that the counter keeps its value between calls */
    static int token = 1000;
    return ++token;
}

/* The same logic with an automatic variable, for comparison. */
int auto_token(void)
{
    int token = 1000;
    return ++token;
}

/* Alternative Concept: caller-owned counter passed by pointer */
int next_token_ptr(int *counter)
{
    return ++(*counter);
}

int main(void)
{
    int s1 = next_token(), s2 = next_token(), s3 = next_token();
    int a1 = auto_token(), a2 = auto_token(), a3 = auto_token();
    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto  : %d %d %d\n", a1, a2, a3);

    /* Evaluation Experiment: unspecified argument evaluation order in C */
    printf("\nSingle printf evaluation experiment (order unspecified in C): ");
    printf("%d %d %d\n", next_token(), next_token(), next_token());

    /* Alternative Concept test */
    int caller_counter = 1000;
    int p1 = next_token_ptr(&caller_counter);
    int p2 = next_token_ptr(&caller_counter);
    int p3 = next_token_ptr(&caller_counter);
    printf("ptr   : %d %d %d (O(1) time, caller-controlled lifetime)\n", p1, p2, p3);
    return 0;
}
