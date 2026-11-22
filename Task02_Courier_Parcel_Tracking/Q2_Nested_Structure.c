/*
 * Task 2 - Q2_Nested_Structure.c
 * Full Courier Franchise entity model with nested Date, Address, Person,
 * ServiceType, and Parcel structures, weight sorting, city filtering,
 * and Task 2.4 access path verification.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic Q2_Nested_Structure.c -o Q2_Nested_Structure
 * Run:     ./Q2_Nested_Structure
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    SERVICE_NORMAL = 0,
    SERVICE_EXPRESS = 1
} ServiceType;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char city[20];
    int pincode;
} Address;

typedef struct {
    char name[32];
    Address addr;
} Person;

typedef struct {
    int id;
    float weight;
    Date booked;
    Person sender;
    Person receiver;
    ServiceType service;
    float charge;
} Parcel;

void sort_parcels_by_weight(Parcel list[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j].weight < list[min_idx].weight) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Parcel tmp = list[i];
            list[i] = list[min_idx];
            list[min_idx] = tmp;
        }
    }
}

void list_parcels_by_city(const Parcel list[], int n, const char *city) {
    printf("\n--- Parcels for Receiver City: %s ---\n", city);
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(list[i].receiver.addr.city, city) == 0) {
            printf("ID=%d | Weight=%.1f kg | Receiver=%s (%s-%d) | Service=%s | Charge=Rs.%.2f\n",
                   list[i].id, list[i].weight, list[i].receiver.name,
                   list[i].receiver.addr.city, list[i].receiver.addr.pincode,
                   list[i].service == SERVICE_EXPRESS ? "Express" : "Normal",
                   list[i].charge);
            found = 1;
        }
    }
    if (!found) {
        printf("No parcels found for %s.\n", city);
    }
}

int main(void) {
    Parcel bookings[4] = {
        {501, 4.5f, {12, 10, 2026}, {"Arun", {"Chennai", 600001}}, {"Bala", {"Madurai", 625001}}, SERVICE_NORMAL, 225.0f},
        {502, 1.2f, {12, 10, 2026}, {"Deepa", {"Trichy", 620001}}, {"Karthik", {"Chennai", 600077}}, SERVICE_EXPRESS, 150.0f},
        {503, 2.8f, {13, 10, 2026}, {"Meera", {"Salem", 636001}}, {"Vijay", {"Coimbatore", 641001}}, SERVICE_NORMAL, 160.0f},
        {504, 3.1f, {13, 10, 2026}, {"Surya", {"Madurai", 625002}}, {"Nisha", {"Chennai", 600028}}, SERVICE_EXPRESS, 280.0f}
    };

    /* Task 2.4 Access Paths for the 3rd parcel (index 2) */
    Parcel *ptr = bookings;
    printf("=== Task 2.4 Access Paths (3rd Parcel Receiver PIN) ===\n");
    printf("Using array & dot operator   (bookings[2].receiver.addr.pincode) : %d\n",
           bookings[2].receiver.addr.pincode);
    printf("Using pointer & arrow operator ((ptr + 2)->receiver.addr.pincode): %d\n",
           (ptr + 2)->receiver.addr.pincode);

    sort_parcels_by_weight(bookings, 4);
    printf("\n--- All Bookings Sorted by Weight ---\n");
    for (int i = 0; i < 4; i++) {
        const Parcel *p = &bookings[i];
        printf("%d | %.1f kg | %s -> %s (%s-%d) | %02d/%02d/%04d | %s | Rs.%.2f\n",
               p->id, p->weight, p->sender.name, p->receiver.name,
               p->receiver.addr.city, p->receiver.addr.pincode,
               p->booked.day, p->booked.month, p->booked.year,
               p->service == SERVICE_EXPRESS ? "Express" : "Normal", p->charge);
    }

    list_parcels_by_city(bookings, 4, "Chennai");

    printf("\n--- Nested Structure Sizes ---\n");
    printf("sizeof(Date)    = %zu bytes\n", sizeof(Date));
    printf("sizeof(Address) = %zu bytes\n", sizeof(Address));
    printf("sizeof(Person)  = %zu bytes\n", sizeof(Person));
    printf("sizeof(Parcel)  = %zu bytes\n", sizeof(Parcel));
    return 0;
}
