/*
 * Task 6 - Q6_Alternative_Linked_List.c
 * Alternative Concept: Singly Linked List of dynamically allocated CanteenItem nodes.
 * Demonstrates O(1) head insertion vs O(n) search/update/deletion,
 * and measures extra pointer memory per node.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q6_Alternative_Linked_List.c -o Q6_Alternative_Linked_List
 * Run:     ./Q6_Alternative_Linked_List
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date { int day, month, year; };
struct Time { int hour, minute; };
enum ItemType { ITEM_PACKAGED, ITEM_COOKED, ITEM_COMBO };

struct ItemNode {
    int id;
    char name[36];
    float price;
    int stock;
    enum ItemType type;
    union {
        struct Date expiry;
        struct Time prep_time;
        struct { int component_ids[3]; int count; } combo;
    } details;
    int units_sold;
    float revenue;
    struct ItemNode *next; /* Extra pointer overhead per item */
};

/* O(1) insertion at the head of the linked list */
struct ItemNode *insert_head(struct ItemNode *head, int id, const char *name,
                             float price, int stock, enum ItemType type) {
    struct ItemNode *node = malloc(sizeof(struct ItemNode));
    if (node == NULL) {
        return head;
    }
    memset(node, 0, sizeof(*node));
    node->id = id;
    strncpy(node->name, name, sizeof(node->name) - 1);
    node->price = price;
    node->stock = stock;
    node->type = type;
    node->next = head;
    return node;
}

/* O(n) linear search by ID */
struct ItemNode *search_item(struct ItemNode *head, int id) {
    struct ItemNode *curr = head;
    while (curr != NULL) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

/* O(n) deletion by ID (requires traversal to locate predecessor) */
struct ItemNode *delete_item(struct ItemNode *head, int id) {
    struct ItemNode *curr = head;
    struct ItemNode *prev = NULL;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return head;
    if (prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
    return head;
}

void free_list(struct ItemNode *head) {
    while (head != NULL) {
        struct ItemNode *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    struct ItemNode *head = NULL;
    head = insert_head(head, 101, "Mango Juice 250ml", 35.0f, 15, ITEM_PACKAGED);
    head = insert_head(head, 102, "Biscuit Pack", 20.0f, 25, ITEM_PACKAGED);
    head = insert_head(head, 103, "Masala Dosa", 50.0f, 12, ITEM_COOKED);

    printf("=== Task 6 Alternative: Singly Linked List ===\n");
    struct ItemNode *found = search_item(head, 102);
    if (found != NULL) {
        found->stock -= 4;
        found->units_sold += 4;
        found->revenue += 4 * found->price;
        printf("Updated %s: Stock=%d, Revenue=Rs.%.2f\n",
               found->name, found->stock, found->revenue);
    }

    head = delete_item(head, 101);
    printf("\nRemaining items after deleting ID 101:\n");
    for (struct ItemNode *p = head; p != NULL; p = p->next) {
        printf("  ID=%d | %-20s | Stock=%d\n", p->id, p->name, p->stock);
    }

    printf("\nsizeof(struct ItemNode) = %zu bytes (includes %zu-byte next pointer)\n",
           sizeof(struct ItemNode), sizeof(struct ItemNode *));
    free_list(head);
    return 0;
}
