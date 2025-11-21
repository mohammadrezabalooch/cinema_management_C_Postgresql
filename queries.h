#ifndef DB_QUERIES_H
#define DB_QUERIES_H

#include <libpq-fe.h>

// این تابع کوئری لیست دیتابیس‌ها را اجرا می‌کند و نتیجه را برمی‌گرداند
PGresult* get_databases(PGconn *conn);
void create_movies_table(PGconn *conn);

// توابع Movie Management
int add_movie(PGconn *conn, const char *title, const char *genre, int release_year);
int edit_movie(PGconn *conn, int movie_id, const char *title, const char *genre, int release_year);
int delete_movie(PGconn *conn, int movie_id);
PGresult* list_movies(PGconn *conn);
PGresult* search_movie(PGconn *conn, const char *search_term);

// توابع User Management
int add_user(PGconn *conn, const char *name, const char *phone);
int edit_user(PGconn *conn, int user_id, const char *name, const char *phone);
int delete_user(PGconn *conn, int user_id);
PGresult* list_users(PGconn *conn);
PGresult* search_user(PGconn *conn, const char *search_term);

// توابع Session Management
int create_session(PGconn *conn, int movie_id, const char *session_time, int hall, int capacity);
int edit_session(PGconn *conn, int session_id, int movie_id, const char *session_time, int hall, int capacity);
int delete_session(PGconn *conn, int session_id);
PGresult* list_sessions(PGconn *conn);
PGresult* search_session(PGconn *conn, int movie_id);

// توابع Ticket Management
int buy_ticket(PGconn *conn, int user_id, int session_id, int seat_number);
int cancel_ticket(PGconn *conn, int ticket_id);
PGresult* list_tickets(PGconn *conn);
PGresult* search_ticket(PGconn *conn, int user_id);

// توابع Reports
PGresult* get_total_sales(PGconn *conn);
PGresult* get_sales_by_movie(PGconn *conn);
PGresult* get_popular_sessions(PGconn *conn);
PGresult* get_active_users(PGconn *conn);
PGresult* get_ticket_availability(PGconn *conn, int session_id);

#endif // DB_QUERIES_H
