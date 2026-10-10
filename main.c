#include "train.h"

int main(void)
{
    int option;
    char username[MAX_TEXT];

    load_trains();

    while (1) {
        printf("\n===== TRAIN TICKET SYSTEM =====\n");
        printf("1. Sign Up\n");
        printf("2. Sign In\n");
        printf("3. Exit\n");
        printf("Enter option: ");

        if (scanf("%d", &option) != 1)
            return 0;

        switch (option) {
        case 1:
            if (register_user())
                printf("Account created successfully.\n");
            break;

        case 2:
            if (login_user(username)) {
                int choice;

                printf("\nWelcome, %s!\n", username);

                do {
                    printf("\n===== MAIN MENU =====\n");
                    printf("1. View Trains\n");
                    printf("2. Book Ticket\n");
                    printf("3. Cancel Ticket\n");
                    printf("4. View Bookings\n");

                    if (strcmp(username, "admin") == 0)
                        printf("5. Add Train\n");

                    printf("0. Logout\n");
                    printf("Enter option: ");

                    if (scanf("%d", &choice) != 1)
                        return 0;

                    switch (choice) {
                    case 1:
                        show_trains();
                        break;
                    case 2:
                        book_ticket();
                        break;
                    case 3:
                        cancel_ticket();
                        break;
                    case 4:
                        show_bookings();
                        break;
                    case 5:
                        if (strcmp(username, "admin") == 0) {
                            add_train();
                        } else {
                            printf("Invalid option.\n");
                        }
                        break;
                    case 0:
                        printf("Logged out.\n");
                        break;
                    default:
                        printf("Invalid option.\n");
                    }

                } while (choice != 0);
            }
            break;

        case 3:
            printf("Thank you for using the system.\n");
            return 0;

        default:
            printf("Please enter a valid option.\n");
        }
    }
}
