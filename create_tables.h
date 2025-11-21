#ifndef CREATE_TABLES_H
#define CREATE_TABLES_H

#include <libpq-fe.h>

void create_tables(PGconn *conn);

#endif