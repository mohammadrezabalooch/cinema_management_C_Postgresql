#ifndef CONNECT_TO_PSQL_H
#define CONNECT_TO_PSQL_H

#include <libpq-fe.h>

// تابعی که به دیتابیس Postgres داخل Docker Compose وصل می‌شود
PGconn* connect_to_db();
// تابعی برای اجرای دستورات SQL (INSERT, UPDATE, DELETE, CREATE) - نتیجه را برمی‌گرداند
PGresult* execute_sql(PGconn *conn, const char *sql);
// تابعی برای اجرای کوئری‌های SELECT که نتیجه برمی‌گردانند
PGresult* execute_sql_query(PGconn *conn, const char *sql);

#endif
