#ifndef DB_QUERIES_H
#define DB_QUERIES_H

#include <libpq-fe.h>

// این تابع کوئری لیست دیتابیس‌ها را اجرا می‌کند و نتیجه را برمی‌گرداند
PGresult* get_databases(PGconn *conn);
void create_movies_table(PGconn *conn);

#endif // DB_QUERIES_H
