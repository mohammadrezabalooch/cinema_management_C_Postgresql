#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "queries.h"

// رنگ‌ها
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// تابع کمکی برای نمایش نتایج
void display_result(PGresult *res) {
    if (!res) {
        printf(RED "No results found.\n" RESET);
        return;
    }
    
    int rows = PQntuples(res);
    int cols = PQnfields(res);
    
    if (rows == 0) {
        printf(YELLOW "No records found.\n" RESET);
        return;
    }
    
    // نمایش هدرها
    for (int j = 0; j < cols; j++) {
        printf(CYAN "%-20s" RESET, PQfname(res, j));
    }
    printf("\n");
    printf("------------------------------------------------------------\n");
    
    // نمایش داده‌ها
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%-20s", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

// ---- Main Menu ----
void mainMenu(PGconn *conn) {
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
            case 1: movieMenu(conn); break;
            case 2: userMenu(conn); break;
            case 3: sessionMenu(conn); break;
            case 4: ticketMenu(conn); break;
            case 5: reportMenu(conn); break;
            case 0:
                printf(RED "Exiting program...\n" RESET);
                break;
            default:
                printf(RED "Invalid choice!\n" RESET);
        }

    } while (choice != 0);
}


// ---- Generic sub-menu function (each one is colored the same way) ----

void movieMenu(PGconn *conn) {
    int choice;
    char title[100], genre[50], search_term[100];
    int movie_id, release_year;
    PGresult *res;
    
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
        getchar(); // برای خالی کردن buffer

        switch (choice) {
            case 1:
                printf("Enter movie title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter genre: ");
                fgets(genre, sizeof(genre), stdin);
                genre[strcspn(genre, "\n")] = 0;
                printf("Enter release year: ");
                scanf("%d", &release_year);
                add_movie(conn, title, genre, release_year);
                break;
            case 2:
                printf("Enter movie ID to edit: ");
                scanf("%d", &movie_id);
                getchar();
                printf("Enter new title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                printf("Enter new genre: ");
                fgets(genre, sizeof(genre), stdin);
                genre[strcspn(genre, "\n")] = 0;
                printf("Enter new release year: ");
                scanf("%d", &release_year);
                edit_movie(conn, movie_id, title, genre, release_year);
                break;
            case 3:
                printf("Enter movie ID to delete: ");
                scanf("%d", &movie_id);
                delete_movie(conn, movie_id);
                break;
            case 4:
                res = list_movies(conn);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 5:
                printf("Enter search term: ");
                fgets(search_term, sizeof(search_term), stdin);
                search_term[strcspn(search_term, "\n")] = 0;
                res = search_movie(conn, search_term);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void userMenu(PGconn *conn) {
    int choice;
    char name[100], phone[20], search_term[100];
    int user_id;
    PGresult *res;
    
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
        getchar();

        switch (choice) {
            case 1:
                printf("Enter user name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter phone number: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;
                add_user(conn, name, phone);
                break;
            case 2:
                printf("Enter user ID to edit: ");
                scanf("%d", &user_id);
                getchar();
                printf("Enter new name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter new phone: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = 0;
                edit_user(conn, user_id, name, phone);
                break;
            case 3:
                printf("Enter user ID to delete: ");
                scanf("%d", &user_id);
                delete_user(conn, user_id);
                break;
            case 4:
                res = list_users(conn);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 5:
                printf("Enter search term: ");
                fgets(search_term, sizeof(search_term), stdin);
                search_term[strcspn(search_term, "\n")] = 0;
                res = search_user(conn, search_term);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void sessionMenu(PGconn *conn) {
    int choice;
    char session_time[50];
    int session_id, movie_id, hall, capacity;
    PGresult *res;
    
    do {
        printf("\n" BLUE "----------- Session Management -----------\n" RESET);
        printf("1. Create Session\n");
        printf("2. Edit Session\n");
        printf("3. Delete Session\n");
        printf("4. List Sessions\n");
        printf("5. Search Session by Movie\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter movie ID: ");
                scanf("%d", &movie_id);
                printf("Enter session time (YYYY-MM-DD HH:MM:SS): ");
                getchar();
                fgets(session_time, sizeof(session_time), stdin);
                session_time[strcspn(session_time, "\n")] = 0;
                printf("Enter hall number: ");
                scanf("%d", &hall);
                printf("Enter capacity: ");
                scanf("%d", &capacity);
                create_session(conn, movie_id, session_time, hall, capacity);
                break;
            case 2:
                printf("Enter session ID to edit: ");
                scanf("%d", &session_id);
                printf("Enter movie ID: ");
                scanf("%d", &movie_id);
                printf("Enter session time (YYYY-MM-DD HH:MM:SS): ");
                getchar();
                fgets(session_time, sizeof(session_time), stdin);
                session_time[strcspn(session_time, "\n")] = 0;
                printf("Enter hall number: ");
                scanf("%d", &hall);
                printf("Enter capacity: ");
                scanf("%d", &capacity);
                edit_session(conn, session_id, movie_id, session_time, hall, capacity);
                break;
            case 3:
                printf("Enter session ID to delete: ");
                scanf("%d", &session_id);
                delete_session(conn, session_id);
                break;
            case 4:
                res = list_sessions(conn);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 5:
                printf("Enter movie ID: ");
                scanf("%d", &movie_id);
                res = search_session(conn, movie_id);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void ticketMenu(PGconn *conn) {
    int choice;
    int ticket_id, user_id, session_id, seat_number;
    PGresult *res;
    
    do {
        printf("\n" BLUE "----------- Ticket Management -----------\n" RESET);
        printf("1. Buy Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. List Tickets\n");
        printf("4. Search Tickets by User\n");
        printf("0. Back\n");

        printf(GREEN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter user ID: ");
                scanf("%d", &user_id);
                printf("Enter session ID: ");
                scanf("%d", &session_id);
                printf("Enter seat number: ");
                scanf("%d", &seat_number);
                buy_ticket(conn, user_id, session_id, seat_number);
                break;
            case 2:
                printf("Enter ticket ID to cancel: ");
                scanf("%d", &ticket_id);
                cancel_ticket(conn, ticket_id);
                break;
            case 3:
                res = list_tickets(conn);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 4:
                printf("Enter user ID: ");
                scanf("%d", &user_id);
                res = search_ticket(conn, user_id);
                if (res) {
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}

void reportMenu(PGconn *conn) {
    int choice;
    int session_id;
    PGresult *res;
    
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
            case 1:
                res = get_total_sales(conn);
                if (res) {
                    printf("\n" GREEN "Total Tickets Sold: " RESET);
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 2:
                res = get_sales_by_movie(conn);
                if (res) {
                    printf("\n" GREEN "Sales by Movie:\n" RESET);
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 3:
                res = get_popular_sessions(conn);
                if (res) {
                    printf("\n" GREEN "Most Popular Sessions:\n" RESET);
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 4:
                res = get_active_users(conn);
                if (res) {
                    printf("\n" GREEN "Active Users:\n" RESET);
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 5:
                printf("Enter session ID: ");
                scanf("%d", &session_id);
                res = get_ticket_availability(conn, session_id);
                if (res) {
                    printf("\n" GREEN "Ticket Availability:\n" RESET);
                    display_result(res);
                    PQclear(res);
                }
                break;
            case 0: break;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    } while (choice != 0);
}
