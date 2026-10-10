#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 100
#define MAX_TEXT 50
#define SEATS 3

#define TRAIN_FILE "data/trains.txt"
#define USER_FILE "data/users.dat"
#define BOOKING_FILE "data/passengers.dat"

typedef struct {
    int number;
    char name[MAX_TEXT];
    char source[MAX_TEXT];
    char destination[MAX_TEXT];
} Train;

typedef struct {
    char username[MAX_TEXT];
    char password[MAX_TEXT];
} User;

typedef struct {
    int train_number;
    int seat_number;
    char passenger_name[MAX_TEXT];
    int age;
    char journey_date[20];
} Ticket;

extern Train trains[MAX_TRAINS];
extern int train_count;

void load_trains(void);
void save_trains(void);
void show_trains(void);
void add_train(void);

int register_user(void);
int login_user(char username[]);

int seat_available(int train_number, int seat_number);
int available_seats(int train_number);
int save_ticket(Ticket ticket);
void book_ticket(void);
void cancel_ticket(void);
void show_bookings(void);

#endif
