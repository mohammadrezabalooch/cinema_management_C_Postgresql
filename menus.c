#include <stdio.h>
#include "menus.h"

// رنگ‌ها
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// ---- Main Menu ----
void mainMenu() {
    int choice;

    do {
        printf("\n" CYAN "===========================================\n" RESET);
        printf(CYAN "          Cinema Management System\n" RESET);
        printf(CYAN "===========================================\n" RESET);

        printf(YELLOW "1. " RESET "Movie Management\n");
        printf(YELLOW "2. " RESET "User Management\n");
        printf(YELLOW "3. " RESET "Session Management\n");
        printf(YELLOW "4. " RESET "Ticket Management\n");
        printf(YELLOW "5. " RESET "Reports\n");
        printf(RED    "0. Exit\n" RESET);

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: movieMenu(); break;
            case 2: userMenu(); break;
            case 3: sessionMenu(); break;
            case 4: ticketMenu(); break;
            case 5: reportMenu(); break;
            case 0:
                printf(RED "Exiting program...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice!\n" RESET);
        }

    } while (choice != 0);
}


// ---- Generic sub-menu function (each one is colored the same way) ----

void movieMenu() {
    int choice;
    do {
        printf("\n" BLUE "----------- Movie Management -----------\n" RESET);
        printf("1. Add New Movie\n");
        printf("2. Edit Movie\n");
        printf("3. Delete Movie\n");
        printf("4. List Movies\n");
        printf("5. Search Movie\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Adding new movie...\n"); break;
            case 2: printf("Editing movie...\n"); break;
            case 3: printf("Deleting movie...\n"); break;
            case 4: printf("Listing movies...\n"); break;
            case 5: printf("Searching movie...\n"); break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void userMenu() {
    int choice;
    do {
        printf("\n" BLUE "----------- User Management -----------\n" RESET);
        printf("1. Add User\n");
        printf("2. Edit User\n");
        printf("3. Delete User\n");
        printf("4. List Users\n");
        printf("5. Search User\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Adding user...\n"); break;
            case 2: printf("Editing user...\n"); break;
            case 3: printf("Deleting user...\n"); break;
            case 4: printf("Listing users...\n"); break;
            case 5: printf("Searching user...\n"); break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void sessionMenu() {
    int choice;
    do {
        printf("\n" BLUE "----------- Session Management -----------\n" RESET);
        printf("1. Create Session\n");
        printf("2. Edit Session\n");
        printf("3. Delete Session\n");
        printf("4. List Sessions\n");
        printf("5. Search Session\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Creating session...\n"); break;
            case 2: printf("Editing session...\n"); break;
            case 3: printf("Deleting session...\n"); break;
            case 4: printf("Listing sessions...\n"); break;
            case 5: printf("Searching session...\n"); break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void ticketMenu() {
    int choice;
    do {
        printf("\n" BLUE "----------- Ticket Management -----------\n" RESET);
        printf("1. Buy Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. List Tickets\n");
        printf("4. Search Ticket\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Buying ticket...\n"); break;
            case 2: printf("Cancelling ticket...\n"); break;
            case 3: printf("Listing tickets...\n"); break;
            case 4: printf("Searching ticket...\n"); break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void reportMenu() {
    int choice;
    do {
        printf("\n" BLUE "----------- Reports -----------\n" RESET);
        printf("1. Total Sales\n");
        printf("2. Sales by Movie\n");
        printf("3. Most Popular Sessions\n");
        printf("4. Active Users\n");
        printf("5. Ticket Availability\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Generating total sales report...\n"); break;
            case 2: printf("Generating movie sales report...\n"); break;
            case 3: printf("Showing popular sessions...\n"); break;
            case 4: printf("Listing active users...\n"); break;
            case 5: printf("Checking ticket availability...\n"); break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}
