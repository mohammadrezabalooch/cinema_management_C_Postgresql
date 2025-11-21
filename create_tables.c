#include <libpq-fe.h>
#include "connect_to_psql.h"

void create_tables(PGconn *conn) {
    execute_sql(conn,
        "CREATE TABLE IF NOT EXISTS movies ("
        "    movie_id SERIAL PRIMARY KEY,"
        "    title VARCHAR(100),"
        "    genre VARCHAR(50),"
        "    release_year INT"
        ");"
    );

    execute_sql(conn,
        "CREATE TABLE IF NOT EXISTS users ("
        "    user_id SERIAL PRIMARY KEY,"
        "    name VARCHAR(100),"
        "    phone VARCHAR(20)"
        ");"
    );

    execute_sql(conn,
        "CREATE TABLE IF NOT EXISTS sessions ("
        "    session_id SERIAL PRIMARY KEY,"
        "    movie_id INT REFERENCES movies(movie_id),"
        "    session_time TIMESTAMP,"
        "    hall INT,"
        "    capacity INT"
        ");"
    );

    execute_sql(conn,
        "CREATE TABLE IF NOT EXISTS tickets ("
        "    ticket_id SERIAL PRIMARY KEY,"
        "    user_id INT REFERENCES users(user_id),"
        "    session_id INT REFERENCES sessions(session_id),"
        "    seat_number INT"
        ");"
    );
}