#include "train.h"

Train trains[MAX_TRAINS];
int train_count = 0;

void load_trains(void)
{
    FILE *fp = fopen(TRAIN_FILE, "r");
    char line[256];
    Train t;

    train_count = 0;

    if (fp == NULL) {
        printf("Unable to open train data file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%d|%49[^|]|%49[^|]|%49[^\r\n]",
                   &t.number,
                   t.name,
                   t.source,
                   t.destination) == 4) {

            if (train_count < MAX_TRAINS) {
                trains[train_count] = t;
                train_count++;
            }
        }
    }

    fclose(fp);
}

void save_trains(void)
{
    FILE *fp = fopen(TRAIN_FILE, "w");
    int i;

    if (fp == NULL) {
        printf("Unable to save train details.\n");
        return;
    }

    for (i = 0; i < train_count; i++) {
        fprintf(fp, "%d|%s|%s|%s\n",
                trains[i].number,
                trains[i].name,
                trains[i].source,
                trains[i].destination);
    }

    fclose(fp);
}

void show_trains(void)
{
    int i;

    if (train_count == 0) {
        printf("No trains available.\n");
        return;
    }

    printf("\n%-8s %-23s %-16s %-16s %-10s\n",
           "Number", "Train Name", "Source",
           "Destination", "Seats Left");

    for (i = 0; i < train_count; i++) {
        printf("%-8d %-23s %-16s %-16s %-10d\n",
               trains[i].number,
               trains[i].name,
               trains[i].source,
               trains[i].destination,
               available_seats(trains[i].number));
    }
}

void add_train(void)
{
    Train t;
    int i;

    if (train_count >= MAX_TRAINS) {
        printf("Train storage is full.\n");
        return;
    }

    printf("Enter train number: ");
    if (scanf("%d", &t.number) != 1)
        return;

    for (i = 0; i < train_count; i++) {
        if (trains[i].number == t.number) {
            printf("This train number already exists.\n");
            return;
        }
    }

    printf("Enter train name: ");
    scanf(" %49[^\n]", t.name);

    printf("Enter starting station: ");
    scanf(" %49[^\n]", t.source);

    printf("Enter destination station: ");
    scanf(" %49[^\n]", t.destination);

    trains[train_count] = t;
    train_count++;

    save_trains();

    printf("Train added successfully with %d seats.\n", SEATS);
}
