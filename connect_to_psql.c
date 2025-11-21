// connect_to_psql.c
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "connect_to_psql.h"

PGconn* connect_to_db() {
    const char *conninfo =
        "host=localhost port=5432 dbname=postgres user=postgres";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "❌ Database connection failed: %s\n",
                PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }

    printf("✅ Connected to PostgreSQL successfully.\n");
    return conn;
}








void execute_sql(PGconn *conn, const char *sql) {
    PGresult *res = PQexec(conn, sql);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "SQL Error: %s\n", PQerrorMessage(conn));
        PQclear(res);
        exit(1);
    }

    printf("✅ Tables created successfully.\n");

    PQclear(res);
}