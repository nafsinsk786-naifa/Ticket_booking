#include "train.h"

static int train_exists(int number)
{
    int i;

    for (i = 0; i < train_count; i++) {
        if (trains[i].number == number)
            return 1;
    }

    return 0;
}

void book_ticket(void)
{
    Ticket t;
    int train_number;
    int seat;
    int found = 0;

    printf("\nEnter train number: ");

    if (scanf("%d", &train_number) != 1)
        return;

    if (!train_exists(train_number)) {
        printf("Train number not found.\n");
        return;
    }

    for (seat = 1; seat <= SEATS; seat++) {
        if (seat_available(train_number, seat)) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Train is full. No seats available.\n");
        return;
    }

    t.train_number = train_number;
    t.seat_number = seat;

    printf("Enter passenger name: ");
    scanf(" %49[^\n]", t.passenger_name);

    printf("Enter passenger age: ");

    if (scanf("%d", &t.age) != 1 ||
        t.age < 1 || t.age > 120) {
        printf("Invalid age.\n");
        return;
    }

    printf("Enter journey date (DD-MM-YYYY): ");
    scanf("%19s", t.journey_date);

    if (save_ticket(t)) {
        printf("\nTicket booked successfully!\n");
        printf("Train number : %d\n", t.train_number);
        printf("Seat number  : %d\n", t.seat_number);
        printf("Passenger    : %s\n", t.passenger_name);
        printf("Journey date : %s\n", t.journey_date);
    }
}

void cancel_ticket(void)
{
    FILE *fp;
    FILE *temp;
    Ticket t;
    int train_number;
    int seat_number;
    int found = 0;

    printf("Enter train number: ");

    if (scanf("%d", &train_number) != 1)
        return;

    printf("Enter seat number (1-3): ");

    if (scanf("%d", &seat_number) != 1 ||
        seat_number < 1 || seat_number > SEATS) {
        printf("Invalid seat number.\n");
        return;
    }

    fp = fopen(BOOKING_FILE, "rb");

    if (fp == NULL) {
        printf("No tickets have been booked.\n");
        return;
    }

    temp = fopen("data/temp.dat", "wb");

    if (temp == NULL) {
        fclose(fp);
        printf("Unable to create temporary file.\n");
        return;
    }

    while (fread(&t, sizeof(Ticket), 1, fp) == 1) {
        if (t.train_number == train_number &&
            t.seat_number == seat_number) {
            found = 1;
        } else {
            fwrite(&t, sizeof(Ticket), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        remove("data/temp.dat");
        printf("Ticket not found.\n");
        return;
    }

    if (remove(BOOKING_FILE) != 0) {
        printf("Unable to update booking records.\n");
        remove("data/temp.dat");
        return;
    }

    if (rename("data/temp.dat", BOOKING_FILE) != 0) {
        printf("Unable to finalize cancellation.\n");
        return;
    }

    printf("Ticket cancelled successfully.\n");
    printf("Seat %d is available again.\n", seat_number);
}

void show_bookings(void)
{
    FILE *fp = fopen(BOOKING_FILE, "rb");
    Ticket t;
    int count = 0;

    if (fp == NULL) {
        printf("No booking records found.\n");
        return;
    }

    printf("\n===== CONFIRMED BOOKINGS =====\n");

    printf("%-8s %-6s %-24s %-5s %-15s\n",
           "Train", "Seat", "Passenger",
           "Age", "Journey Date");

    while (fread(&t, sizeof(Ticket), 1, fp) == 1) {
        printf("%-8d %-6d %-24s %-5d %-15s\n",
               t.train_number,
               t.seat_number,
               t.passenger_name,
               t.age,
               t.journey_date);

        count++;
    }

    if (count == 0)
        printf("No confirmed bookings.\n");

    fclose(fp);
}
