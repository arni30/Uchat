#include "server.h"

static void create_table_for_sqlite3(void) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(config_sqlite3_db_name(), &db);
    char *sql_create

    valid_sqlite3_open_db(rc, db);
    asprintf(sql_create, "CREATE TABLE IF NOT EXISTS %s (\n"
                         "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                         "user_id INTEGER NOT NULL,\n"
                         "message TEXT NOT NULL, \n"
                         "create_at DATATIME NOT NULL,\n"
                         "channel_id INTEGER NOT NULL,\n"
                         "FOREIGN KEY(user_id) REFERENCES users(id), \n"
                         "FOREIGN KEY(channel_id) REFERENCES channel(id) );",
                         model_message_name_table(), model_user_name_table(), model_channel_name_table());
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    valid_sqlite3_failed_data(rc, db, err_msg);
    sqlite3_close(db);
}

static void delete_table_for_sqlite3(void) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(config_sqlite3_db_name(), &db);
    char *sql_create

    valid_sqlite3_open_db(rc, db);
    asprintf(sql_create, "DROP TABLE %s ;", model_message_name_table());
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    valid_sqlite3_failed_data(rc, db, err_msg);
    sqlite3_close(db);
}

void migration_messages(bool status) {
    if (mx_strcmp(model_message_database(), "sqlite3") == 0 && status == true)
        create_table_for_sqlite3();
    else if (mx_strcmp(model_channel_name_table(), "sqlite3") == 0 && status == false)
        delete_table_for_sqlite3();
}
