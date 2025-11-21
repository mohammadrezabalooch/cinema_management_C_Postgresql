#ifndef MENUS_H
#define MENUS_H

#include <libpq-fe.h>

// اعلام تمام فانکشن‌های منو
void mainMenu(PGconn *conn);
void movieMenu(PGconn *conn);
void userMenu(PGconn *conn);
void sessionMenu(PGconn *conn);
void ticketMenu(PGconn *conn);
void reportMenu(PGconn *conn);

// تابع کمکی برای نمایش نتایج
void display_result(PGresult *res);

#endif