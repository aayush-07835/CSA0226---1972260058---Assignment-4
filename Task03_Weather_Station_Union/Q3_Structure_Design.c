/*
 * Task 3 - Q3_Structure_Design.c
 * Normal structure design holding all three sensor fields simultaneously
 * (for size and memory comparison against tagged union).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q3_Structure_Design.c -o Q3_Structure_Design
 * Run:     ./Q3_Structure_Design
 */

#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading_struct {
    enum kind type;
    float celsius;
    int percent;
    char status[8];
};

void show_struct(const struct reading_struct *r) {
    switch (r->type) {
        case TEMPERATURE:
            printf("Temp %.1f C\n", r->celsius);
            break;
        case HUMIDITY:
            printf("Humidity %d %%\n", r->percent);
            break;
        case STATUS:
            printf("Status %s\n", r->status);
            break;
    }
}

int main(void) {
    struct reading_struct log[3] = {
        {TEMPERATURE, 31.5f, 0, ""},
        {HUMIDITY, 0.0f, 68, ""},
        {STATUS, 0.0f, 0, "OK"}
    };

    printf("=== Q3 Normal Structure Design ===\n");
    printf("sizeof(enum kind)              = %zu bytes\n", sizeof(enum kind));
    printf("sizeof(struct reading_struct)  = %zu bytes\n", sizeof(struct reading_struct));
    printf("Memory for 10,000 packets      = %zu bytes\n", 10000 * sizeof(struct reading_struct));
    for (int i = 0; i < 3; i++) {
        show_struct(&log[i]);
    }
    return 0;
}
