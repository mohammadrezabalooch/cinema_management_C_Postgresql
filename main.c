#include <stdio.h>
#include "connect_to_psql.h"
#include "queries.h"
#include "create_tables.h"
#include "menus.h"

int main() {

    PGconn *conn = connect_to_db();
    if (!conn) {
        return 1;
    }

    // گرفتن لیست دیتابیس‌ها با استفاده از تابعی که از db_queries.c میاد
    PGresult *res = get_databases(conn);
    if (!res) {
        PQfinish(conn);
        return 1;
    }

    int rows = PQntuples(res);
    int cols = PQnfields(res);

    printf("✅ List of databases:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%s\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    // فراخوانی تابع برای ایجاد جدول movies فقط یک بار اجرا کافیست
    //create_movies_table(conn);

    create_tables(conn);
    
    PQclear(res);
    
    mainMenu(conn);
    
    PQfinish(conn);

    //منو قدیمی
    //list_of_items();
    return 0;
}