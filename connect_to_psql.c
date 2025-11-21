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
