/*
 * Task 3 - Q3_Alternative_Storage.c
 * Compares Tagged Union against:
 *   1. Three separate arrays (one per packet type)
 *   2. Dynamically allocated objects referenced via void * pointers
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q3_Alternative_Storage.c -o Q3_Alternative_Storage
 * Run:     ./Q3_Alternative_Storage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };

struct reading_union {
    enum kind type;
    union {
        float celsius;
        int percent;
        char status[8];
    } value;
};

struct void_packet {
    enum kind type;
    void *data;
};

int main(void) {
    /* Design 1: Three separate arrays */
    float temps[1] = {31.5f};
    int humids[1] = {68};
    char statuses[1][8] = {"OK"};

    /* Design 2: Heap-allocated objects via void* */
    struct void_packet vpackets[3];
    float *t_ptr = malloc(sizeof(float));
    int *h_ptr = malloc(sizeof(int));
    char *s_ptr = malloc(8 * sizeof(char));

    if (!t_ptr || !h_ptr || !s_ptr) {
        free(t_ptr);
        free(h_ptr);
        free(s_ptr);
        return 1;
    }

    *t_ptr = 31.5f;
    *h_ptr = 68;
    strcpy(s_ptr, "OK");

    vpackets[0] = (struct void_packet){TEMPERATURE, t_ptr};
    vpackets[1] = (struct void_packet){HUMIDITY, h_ptr};
    vpackets[2] = (struct void_packet){STATUS, s_ptr};

    printf("=== Q3 Alternative Storage Comparison ===\n");
    printf("Separate arrays element sizes: float=%zu B, int=%zu B, char[8]=%zu B\n",
           sizeof(temps[0]), sizeof(humids[0]), sizeof(statuses[0]));
    printf("Tagged union struct size     : %zu bytes/packet (no heap overhead)\n",
           sizeof(struct reading_union));
    printf("void* wrapper struct size    : %zu bytes/packet + heap payload + allocator metadata\n",
           sizeof(struct void_packet));

    for (int i = 0; i < 3; i++) {
        switch (vpackets[i].type) {
            case TEMPERATURE:
                printf("void* Temp %.1f C\n", *(float *)vpackets[i].data);
                break;
            case HUMIDITY:
                printf("void* Humidity %d %%\n", *(int *)vpackets[i].data);
                break;
            case STATUS:
                printf("void* Status %s\n", (char *)vpackets[i].data);
                break;
        }
    }

    free(t_ptr);
    free(h_ptr);
    free(s_ptr);
    return 0;
}
