#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct
{
    int i_id;
    char c_name[20];
    int i_quantity;
    float f_price;
} Item;

Item inventory[MAX];
int item_count = 0;

int validate_user(char *, char *);
int main()
{
    while (1)
    {
        printf("Welcome to the Awesome Inventory Management System\n");
        printf("Please login to continue\n");
        char username[20], password[20];
        printf("Enter username: ");
        scanf(" %s", username);
        printf("Enter password: ");
        scanf(" %s", password);
        if(validate_user(username,password)){
            printf("Login successful\n");
            printf("Welcome %s", username);
            printf("What do you want to do?\n");
            printf("1. Add item\n");
            printf("2. View item\n");
            printf("3. Update item\n");
            printf("4. Delete item\n");
            printf("5. Exit\n");
        }
        else{
            printf("Invalid username or password\n");
        }
    }
    return 0;
}

int validate_user(char *username, char *password)
{
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file\n");
        exit(1);
    }
    char line[100];
    while (fgets(line, sizeof(line), fp))
    {
        char *token = strtok(line, ",");
        if (strcmp(token, username) == 0)
        {
            token = strtok(NULL, ",");
            token[strcspn(token, "\n")] = '\0';
            if (strcmp(token, password) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);

    return 0;
}