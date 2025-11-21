#ifndef CONNECT_TO_PSQL_H
#define CONNECT_TO_PSQL_H

#include <libpq-fe.h>

// تابعی که به دیتابیس Postgres داخل Docker Compose وصل می‌شود
PGconn* connect_to_db();
void execute_sql(PGconn *conn, const char *sql);

#endif
