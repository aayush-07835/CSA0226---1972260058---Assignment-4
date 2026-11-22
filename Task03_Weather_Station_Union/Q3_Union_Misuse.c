/*
 * Task 3 - Q3_Union_Misuse.c
 * Misuse Experiment (Task 3.4):
 * Stores a float temperature in the union and then reads the inactive int humidity member.
 * Demonstrates why reading an inactive union member is non-portable / implementation-dependent.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q3_Union_Misuse.c -o Q3_Union_Misuse
 * Run:     ./Q3_Union_Misuse
 */

#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading {
    enum kind type;
    union {
        float celsius;
        int   percent;
        char  status[8];
    } value;
};

int main(void) {
    struct reading r;
    r.type = TEMPERATURE;
    r.value.celsius = 31.5f;

    printf("=== Q3 Union Misuse Experiment ===\n");
    printf("Stored active member (celsius)   : %.1f\n", r.value.celsius);
    /* Misuse: reading inactive member 'percent' without updating union */
    printf("Read inactive member (percent)   : %d\n", r.value.percent);
    printf("Hex representation of those bits : 0x%08X\n", (unsigned int)r.value.percent);
    printf("Note: 31.5f in IEEE-754 single-precision is 0x41FC0000 (decimal 1107034112).\n");
    printf("Reading an inactive union member reinterprets raw bytes and is implementation-defined/non-portable.\n");
    return 0;
}
