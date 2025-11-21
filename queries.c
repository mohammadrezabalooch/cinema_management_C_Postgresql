#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queries.h"
#include "connect_to_psql.h"

// تابعی که کوئری گرفتن دیتابیس‌ها را انجام می‌دهد
PGresult* get_databases(PGconn *conn) {
    return execute_sql_query(conn, "SELECT datname FROM pg_database;");
}

// تابعی برای ایجاد جدول movies
void create_movies_table(PGconn *conn) {
    const char *create_table_query = 
        "CREATE TABLE IF NOT EXISTS movies ("
        "id SERIAL PRIMARY KEY, "
        "title VARCHAR(255) NOT NULL, "
        "director VARCHAR(255), "
        "release_year INTEGER, "
        "genre VARCHAR(50), "
        "duration INTEGER"
        ");";

    execute_sql(conn, create_table_query);
    printf("✅ Table 'movies' created successfully.\n");
}

// ========== Movie Management Functions ==========

int add_movie(PGconn *conn, const char *title, const char *genre, int release_year) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO movies (title, genre, release_year) VALUES ('%s', '%s', %d) RETURNING movie_id;",
        title, genre, release_year);
    
    PGresult *res = execute_sql_query(conn, query);
    if (!res) {
        return 0;
    }
    
    int movie_id = atoi(PQgetvalue(res, 0, 0));
    printf("✅ Movie added successfully with ID: %d\n", movie_id);
    PQclear(res);
    return movie_id;
}

int edit_movie(PGconn *conn, int movie_id, const char *title, const char *genre, int release_year) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE movies SET title = '%s', genre = '%s', release_year = %d WHERE movie_id = %d;",
        title, genre, release_year, movie_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ Movie with ID %d not found.\n", movie_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ Movie updated successfully.\n");
    PQclear(res);
    return 1;
}

int delete_movie(PGconn *conn, int movie_id) {
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM movies WHERE movie_id = %d;", movie_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ Movie with ID %d not found.\n", movie_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ Movie deleted successfully.\n");
    PQclear(res);
    return 1;
}

PGresult* list_movies(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT movie_id, title, genre, release_year FROM movies ORDER BY movie_id;");
}

PGresult* search_movie(PGconn *conn, const char *search_term) {
    char query[512];
    snprintf(query, sizeof(query), 
        "SELECT movie_id, title, genre, release_year FROM movies WHERE title ILIKE '%%%s%%' OR genre ILIKE '%%%s%%';",
        search_term, search_term);
    
    return execute_sql_query(conn, query);
}

// ========== User Management Functions ==========

int add_user(PGconn *conn, const char *name, const char *phone) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO users (name, phone) VALUES ('%s', '%s') RETURNING user_id;",
        name, phone);
    
    PGresult *res = execute_sql_query(conn, query);
    if (!res) {
        return 0;
    }
    
    int user_id = atoi(PQgetvalue(res, 0, 0));
    printf("✅ User added successfully with ID: %d\n", user_id);
    PQclear(res);
    return user_id;
}

int edit_user(PGconn *conn, int user_id, const char *name, const char *phone) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE users SET name = '%s', phone = '%s' WHERE user_id = %d;",
        name, phone, user_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ User with ID %d not found.\n", user_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ User updated successfully.\n");
    PQclear(res);
    return 1;
}

int delete_user(PGconn *conn, int user_id) {
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM users WHERE user_id = %d;", user_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ User with ID %d not found.\n", user_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ User deleted successfully.\n");
    PQclear(res);
    return 1;
}

PGresult* list_users(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT user_id, name, phone FROM users ORDER BY user_id;");
}

PGresult* search_user(PGconn *conn, const char *search_term) {
    char query[512];
    snprintf(query, sizeof(query), 
        "SELECT user_id, name, phone FROM users WHERE name ILIKE '%%%s%%' OR phone ILIKE '%%%s%%';",
        search_term, search_term);
    
    return execute_sql_query(conn, query);
}

// ========== Session Management Functions ==========

int create_session(PGconn *conn, int movie_id, const char *session_time, int hall, int capacity) {
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO sessions (movie_id, session_time, hall, capacity) VALUES (%d, '%s', %d, %d) RETURNING session_id;",
        movie_id, session_time, hall, capacity);
    
    PGresult *res = execute_sql_query(conn, query);
    if (!res) {
        return 0;
    }
    
    int session_id = atoi(PQgetvalue(res, 0, 0));
    printf("✅ Session created successfully with ID: %d\n", session_id);
    PQclear(res);
    return session_id;
}

int edit_session(PGconn *conn, int session_id, int movie_id, const char *session_time, int hall, int capacity) {
    char query[512];
    snprintf(query, sizeof(query), 
        "UPDATE sessions SET movie_id = %d, session_time = '%s', hall = %d, capacity = %d WHERE session_id = %d;",
        movie_id, session_time, hall, capacity, session_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ Session with ID %d not found.\n", session_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ Session updated successfully.\n");
    PQclear(res);
    return 1;
}

int delete_session(PGconn *conn, int session_id) {
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM sessions WHERE session_id = %d;", session_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ Session with ID %d not found.\n", session_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ Session deleted successfully.\n");
    PQclear(res);
    return 1;
}

PGresult* list_sessions(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT s.session_id, m.title, s.session_time, s.hall, s.capacity "
        "FROM sessions s JOIN movies m ON s.movie_id = m.movie_id "
        "ORDER BY s.session_time;");
}

PGresult* search_session(PGconn *conn, int movie_id) {
    char query[256];
    snprintf(query, sizeof(query), 
        "SELECT s.session_id, m.title, s.session_time, s.hall, s.capacity "
        "FROM sessions s JOIN movies m ON s.movie_id = m.movie_id "
        "WHERE s.movie_id = %d ORDER BY s.session_time;",
        movie_id);
    
    return execute_sql_query(conn, query);
}

// ========== Ticket Management Functions ==========

int buy_ticket(PGconn *conn, int user_id, int session_id, int seat_number) {
    // بررسی اینکه صندلی قبلاً رزرو نشده باشد
    char check_query[256];
    snprintf(check_query, sizeof(check_query), 
        "SELECT COUNT(*) FROM tickets WHERE session_id = %d AND seat_number = %d;",
        session_id, seat_number);
    
    PGresult *check_res = execute_sql_query(conn, check_query);
    if (check_res) {
        int count = atoi(PQgetvalue(check_res, 0, 0));
        if (count > 0) {
            printf("❌ Seat %d is already taken for this session.\n", seat_number);
            PQclear(check_res);
            return 0;
        }
        PQclear(check_res);
    }
    
    // بررسی ظرفیت سالن
    char capacity_query[256];
    snprintf(capacity_query, sizeof(capacity_query), 
        "SELECT capacity, (SELECT COUNT(*) FROM tickets WHERE session_id = %d) as sold "
        "FROM sessions WHERE session_id = %d;",
        session_id, session_id);
    
    PGresult *cap_res = execute_sql_query(conn, capacity_query);
    if (cap_res) {
        int capacity = atoi(PQgetvalue(cap_res, 0, 0));
        int sold = atoi(PQgetvalue(cap_res, 0, 1));
        if (sold >= capacity) {
            printf("❌ Session is full. No available seats.\n");
            PQclear(cap_res);
            return 0;
        }
        PQclear(cap_res);
    }
    
    // خرید بلیط
    char query[512];
    snprintf(query, sizeof(query), 
        "INSERT INTO tickets (user_id, session_id, seat_number) VALUES (%d, %d, %d) RETURNING ticket_id;",
        user_id, session_id, seat_number);
    
    PGresult *res = execute_sql_query(conn, query);
    if (!res) {
        return 0;
    }
    
    int ticket_id = atoi(PQgetvalue(res, 0, 0));
    printf("✅ Ticket purchased successfully with ID: %d\n", ticket_id);
    PQclear(res);
    return ticket_id;
}

int cancel_ticket(PGconn *conn, int ticket_id) {
    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM tickets WHERE ticket_id = %d;", ticket_id);
    
    PGresult *res = execute_sql(conn, query);
    if (!res) {
        return 0;
    }
    
    if (PQcmdTuples(res)[0] == '0') {
        printf("❌ Ticket with ID %d not found.\n", ticket_id);
        PQclear(res);
        return 0;
    }
    
    printf("✅ Ticket cancelled successfully.\n");
    PQclear(res);
    return 1;
}

PGresult* list_tickets(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT t.ticket_id, u.name, m.title, s.session_time, t.seat_number "
        "FROM tickets t "
        "JOIN users u ON t.user_id = u.user_id "
        "JOIN sessions s ON t.session_id = s.session_id "
        "JOIN movies m ON s.movie_id = m.movie_id "
        "ORDER BY t.ticket_id;");
}

PGresult* search_ticket(PGconn *conn, int user_id) {
    char query[512];
    snprintf(query, sizeof(query), 
        "SELECT t.ticket_id, u.name, m.title, s.session_time, t.seat_number "
        "FROM tickets t "
        "JOIN users u ON t.user_id = u.user_id "
        "JOIN sessions s ON t.session_id = s.session_id "
        "JOIN movies m ON s.movie_id = m.movie_id "
        "WHERE t.user_id = %d ORDER BY s.session_time;",
        user_id);
    
    return execute_sql_query(conn, query);
}

// ========== Report Functions ==========

PGresult* get_total_sales(PGconn *conn) {
    return execute_sql_query(conn, "SELECT COUNT(*) as total_tickets FROM tickets;");
}

PGresult* get_sales_by_movie(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT m.title, COUNT(t.ticket_id) as ticket_count "
        "FROM movies m "
        "LEFT JOIN sessions s ON m.movie_id = s.movie_id "
        "LEFT JOIN tickets t ON s.session_id = t.session_id "
        "GROUP BY m.movie_id, m.title "
        "ORDER BY ticket_count DESC;");
}

PGresult* get_popular_sessions(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT s.session_id, m.title, s.session_time, s.hall, COUNT(t.ticket_id) as ticket_count "
        "FROM sessions s "
        "JOIN movies m ON s.movie_id = m.movie_id "
        "LEFT JOIN tickets t ON s.session_id = t.session_id "
        "GROUP BY s.session_id, m.title, s.session_time, s.hall "
        "ORDER BY ticket_count DESC "
        "LIMIT 10;");
}

PGresult* get_active_users(PGconn *conn) {
    return execute_sql_query(conn, 
        "SELECT u.user_id, u.name, COUNT(t.ticket_id) as ticket_count "
        "FROM users u "
        "LEFT JOIN tickets t ON u.user_id = t.user_id "
        "GROUP BY u.user_id, u.name "
        "HAVING COUNT(t.ticket_id) > 0 "
        "ORDER BY ticket_count DESC;");
}

PGresult* get_ticket_availability(PGconn *conn, int session_id) {
    char query[512];
    snprintf(query, sizeof(query), 
        "SELECT s.capacity, COUNT(t.ticket_id) as sold, (s.capacity - COUNT(t.ticket_id)) as available "
        "FROM sessions s "
        "LEFT JOIN tickets t ON s.session_id = t.session_id "
        "WHERE s.session_id = %d "
        "GROUP BY s.session_id, s.capacity;",
        session_id);
    
    return execute_sql_query(conn, query);
}