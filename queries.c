#include <stdio.h>
#include "queries.h"

// تابعی که کوئری گرفتن دیتابیس‌ها را انجام می‌دهد
PGresult* get_databases(PGconn *conn) {
    // ارسال کوئری برای گرفتن لیست دیتابیس‌ها
    PGresult *res = PQexec(conn, "SELECT datname FROM pg_database;");
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return NULL;
    }

    return res;
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

    PGresult *res = PQexec(conn, create_table_query);

    // بررسی وضعیت اجرای کوئری
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Table creation failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("✅ Table 'movies' created successfully.\n");
    PQclear(res);
}