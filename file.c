#include "train.h"

int seat_available(int train_number, int seat_number)
{
    FILE *fp = fopen(BOOKING_FILE, "rb");
    Ticket t;

    if (fp == NULL)
        return 1;

    while (fread(&t, sizeof(Ticket), 1, fp) == 1) {
        if (t.train_number == train_number &&
            t.seat_number == seat_number) {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

int available_seats(int train_number)
{
    int seat;
    int count = 0;

    for (seat = 1; seat <= SEATS; seat++) {
        if (seat_available(train_number, seat))
            count++;
    }

    return count;
}

int save_ticket(Ticket ticket)
{
    FILE *fp = fopen(BOOKING_FILE, "ab");

    if (fp == NULL) {
        printf("Unable to open booking file.\n");
        return 0;
    }

    if (fwrite(&ticket, sizeof(Ticket), 1, fp) != 1) {
        fclose(fp);
        printf("Unable to save ticket.\n");
        return 0;
    }

    fclose(fp);
    return 1;
}
