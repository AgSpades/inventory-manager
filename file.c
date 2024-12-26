#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct
{
    int id;
    char name[20];
    int quantity;
    float price;
} Item;

Item inventory[MAX];
int item_count = 0;

int validate_user(char *, char *);
void add_item();
void search_item(char *);
void view_item();
void delete_item(int);
void update_item(int);
int total_value()
{
    int sum = 0;
    for (int i = 0; i < item_count; i++)
    {
        sum += inventory[i].price;
    }

    return sum;
}
int main()
{
    while (1)
    {
        printf("******************************************************************\n");
        printf("\tWelcome to the Awesome Inventory Management System\n");
        printf("******************************************************************\n");
        printf("Please login to continue...\n");
        char username[20], password[20];
        printf("Enter username: ");
        scanf(" %s", username);
        printf("Enter password: ");
        scanf(" %s", password);
        if (validate_user(username, password))
        {
            printf("Login successful!\n");
            printf("\n");
            while (1)
            {
                printf("Welcome %s\n", username);
                printf("What do you want to do?\n");
                printf("1. Add item\n");
                printf("2. Search item\n");
                printf("3. View item\n");
                printf("4. Delete item\n");
                printf("5. Update item\n");
                printf("6. Calculate total value of items in inventory\n");
                printf("7. Exit\n");
                int choice;
                printf("Enter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    printf("Add items to the inventory\n");
                    add_item();
                    break;
                case 2:
                    printf("Search items in the inventory\n");
                    printf("Enter item name to search: ");
                    char search[20];
                    scanf(" %s", search);
                    search_item(search);
                    break;
                case 3:
                    printf("View items in the inventory\n");
                    view_item();
                    break;
                case 4:
                    printf("Delete items from the inventory\n");
                    view_item();
                    printf("Enter item id to delete: ");
                    int id;
                    scanf("%d", &id);
                    delete_item(id);
                    break;
                case 5:
                    printf("Update items in the inventory\n");
                    view_item();
                    printf("Enter the id of the item you want to update:\n");
                    scanf("%d", &id);
                    update_item(id);
                    break;
                case 6:
                    view_item();
                    printf("Total value of items in inventory:");
                    printf("%d\n\n", total_value());
                    break;
                case 7:
                    printf("Exiting...\n");
                    exit(0);
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            printf("Invalid username or password\n");
        }
    }
    return 0;
}

void add_item()
{
    if (item_count >= MAX)
    {
        printf("Inventory is full!");
        return;
    }
    printf("Enter item name: ");
    scanf(" %s", inventory[item_count].name);
    printf("Enter item quantity: ");
    scanf("%d", &inventory[item_count].quantity);
    printf("Enter item price: ");
    scanf("%f", &inventory[item_count].price);
    inventory[item_count].id = item_count + 1;
    item_count++;
}

void view_item()
{
    if (item_count != 0)
    {
        printf("\nItems in the inventory are as follows:\n");
        printf("ID\tNAME\tQUANTITY\tPRICE($)\n\n");
        for (int i = 0; i < item_count; i++)
        {
            printf("%2d\t%s\t%2d\t%.1f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
        }
    }
    else
        printf("No items to display!\n");
    printf("\n");
}

void delete_item(int id)
{
    int len = sizeof(inventory) / sizeof(Item);
    int pos = id - 1;
    if (pos < 0 || pos >= len)
    {
        printf("Invalid id!! Unable to delete\n");
        return;
    }

    for (int i = pos; i < len - 1; i++)
    {
        inventory[i] = inventory[i + 1];
    }

    len--;

    printf("Deleted Succesfully! Inventory after deletion:");

    view_item();
}

void update_item(int id)
{
    int pos = id - 1;
    int len = sizeof(inventory) / sizeof(Item);

    if (pos < 0 || pos >= len)
    {
        printf("Invalid id!! Unable to update\n");
        return;
    }
    while (1)
    {
        printf("Which of the following you want to update?\n");
        printf("1. Item Name\n2. Item Quantity\n3. Item Price\n4. All\n 5.Exit");
        int choice;
        switch (choice)
        {
        case 1:
            char new_name[25];
            printf("Enter new name: ");
            scanf(" %s", new_name);
            strcpy(inventory[pos].name, new_name);
            break;
        case 2:
            int new_qt;
            printf("Enter new quantity: ");
            scanf("%d", new_qt);
            inventory[pos].quantity = new_qt;
            break;
        case 3:
            int new_pr;
            printf("Enter new price: ");
            scanf("%d", new_pr);
            inventory[pos].price = new_pr;
            break;
        case 4:
            printf("Enter new name: ");
            scanf(" %s", new_name);
            strcpy(inventory[pos].name, new_name);
            printf("Enter new quantity: ");
            scanf("%d", new_qt);
            inventory[pos].quantity = new_qt;
            printf("Enter new price: ");
            scanf("%d", new_pr);
            inventory[pos].price = new_pr;
            break;
        case 5:
            printf("Exiting...\n");
            return;
        default:
            printf("Invalid Option!\n");
        }
    }
}

void search_item(char *s)
{
    for (int i = 0; i < item_count; i++)
    {
        if (!strcmp(inventory[i].name, s))
        {
            printf("Item found!\n");
            printf("Do you want to view the quantity?(Y/N)\n");
            char ch;
            scanf(" %c", &ch);
            if (ch == 'Y' || ch == 'y')
                printf("Available quantity for %s is %d\n\n", inventory[i].name, inventory[i].quantity);
            else
                break;
        }
    }
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