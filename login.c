#include "train.h"

int register_user(void)
{
    FILE *fp;
    User new_user;
    User old_user;

    fp = fopen(USER_FILE, "a+b");

    if (fp == NULL) {
        printf("Unable to access user file.\n");
        return 0;
    }

    printf("Choose username: ");
    scanf("%49s", new_user.username);

    rewind(fp);

    while (fread(&old_user, sizeof(User), 1, fp) == 1) {
        if (strcmp(old_user.username,
                   new_user.username) == 0) {
            printf("Username already exists.\n");
            fclose(fp);
            return 0;
        }
    }

    printf("Choose password: ");
    scanf("%49s", new_user.password);

    fseek(fp, 0, SEEK_END);

    if (fwrite(&new_user, sizeof(User), 1, fp) != 1) {
        printf("Unable to save account.\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

int login_user(char username[])
{
    FILE *fp;
    User saved_user;
    char entered_username[MAX_TEXT];
    char entered_password[MAX_TEXT];

    fp = fopen(USER_FILE, "rb");

    if (fp == NULL) {
        printf("No accounts found. Create an account first.\n");
        return 0;
    }

    printf("Username: ");
    scanf("%49s", entered_username);

    printf("Password: ");
    scanf("%49s", entered_password);

    while (fread(&saved_user, sizeof(User), 1, fp) == 1) {
        if (strcmp(saved_user.username, entered_username) == 0 &&
            strcmp(saved_user.password, entered_password) == 0) {
            strcpy(username, saved_user.username);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("Incorrect username or password.\n");

    return 0;
}
