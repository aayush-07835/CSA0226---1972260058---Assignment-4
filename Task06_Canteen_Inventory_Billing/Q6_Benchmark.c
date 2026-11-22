/*
 * Task 6 - Q6_Benchmark.c
 * Measures memory footprint and traversal/insertion/search counts comparing
 * Array of Structures vs Singly Linked List for N = 50, 500, 5000 items.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q6_Benchmark.c -o Q6_Benchmark
 * Run:     ./Q6_Benchmark
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ArrayItem {
    int id;
    char name[36];
    float price;
    int stock;
    int type;
    union {
        int d[3];
        int t[2];
        int c[4];
    } details;
    int units_sold;
    float revenue;
};

struct ListItem {
    int id;
    char name[36];
    float price;
    int stock;
    int type;
    union {
        int d[3];
        int t[2];
        int c[4];
    } details;
    int units_sold;
    float revenue;
    struct ListItem *next;
};

static double elapsed_ms(clock_t start, clock_t end) {
    return 1000.0 * (double)(end - start) / (double)CLOCKS_PER_SEC;
}

int main(void) {
    int sizes[3] = {50, 500, 5000};
    printf("=== Task 6 Array of Structures vs Linked List Benchmark ===\n");
    printf("sizeof(struct ArrayItem) = %zu bytes\n", sizeof(struct ArrayItem));
    printf("sizeof(struct ListItem)  = %zu bytes\n\n", sizeof(struct ListItem));
    printf("%-6s | %-12s | %-12s | %-14s | %-14s\n",
           "N", "Array Bytes", "List Bytes", "Array Search ms", "List Search ms");
    printf("-------+--------------+--------------+----------------+---------------\n");

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        struct ArrayItem *arr = malloc((size_t)n * sizeof(struct ArrayItem));
        struct ListItem *head = NULL;
        for (int i = 0; i < n; i++) {
            arr[i].id = i + 1;
            struct ListItem *node = malloc(sizeof(struct ListItem));
            node->id = n - i;
            node->next = head;
            head = node;
        }

        clock_t t1 = clock();
        volatile int found_a = 0;
        for (int r = 0; r < 200; r++) {
            for (int i = 0; i < n; i++) {
                if (arr[i].id == n) { found_a = arr[i].id; break; }
            }
        }
        clock_t t2 = clock();

        clock_t t3 = clock();
        volatile int found_l = 0;
        for (int r = 0; r < 200; r++) {
            for (struct ListItem *p = head; p != NULL; p = p->next) {
                if (p->id == n) { found_l = p->id; break; }
            }
        }
        clock_t t4 = clock();
        (void)found_a;
        (void)found_l;

        printf("%-6d | %-12zu | %-12zu | %14.4f | %14.4f\n",
               n,
               (size_t)n * sizeof(struct ArrayItem),
               (size_t)n * sizeof(struct ListItem),
               elapsed_ms(t1, t2),
               elapsed_ms(t3, t4));

        free(arr);
        while (head != NULL) {
            struct ListItem *nx = head->next;
            free(head);
            head = nx;
        }
    }
    return 0;
}
