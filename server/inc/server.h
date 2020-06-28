#ifndef UCHAT_SERVER_H
#define UCHAT_SERVER_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <sqlite3.h>
#include "libmx.h"

typedef struct s_clients {
    struct s_clients *next;
    int fd;
    char *name_to;
    char *name_from;
    struct s_clients *first;
}              t_clients;

///Config
char *config_sqlite3_db_name(void);
///end config

///Validation
void valid_check_argc_error(int argc);
void valid_sqlite3_open_db(int rc, sqlite3 *db);
void valid_sqlite3_failed_data(int rc, sqlite3 *db, char *err_msg);
///end validation

///Models
//model_channel
char *model_channel_database(void);
char *model_channel_name_table(void);
char **model_channel_fill_table(void);
//model_delivery_user
char *model_delivery_user_database(void);
char *model_delivery_user_name_table(void);
char **model_delivery_user_fill_table(void);
//model_message
char *model_message_database(void);
char **model_message_name_table(void);
char **model_message_fill_table(void);
//model_user
char *model_user_database(void);
char *model_user_channel_name_table(void);
char **model_user_fill_table(void);
//model_user_channel
char *model_user_channel_database(void);
char *model_user_name_table(void);
char **model_user_channel_fill_table(void);
///end models

///Migrations
void migration(char *argv);
void migration_users(bool status);
void migration_channels(bool status);
void migration_messages(bool status);
void migration_user_channel(bool status);
void migration_delivery_user(bool status);
///end migrations

//CRUD
void create_databases(char *database, char *table, char *fill_table, char *value_table);
void read_database(char *database, char *table, char *set, char *where);
void update_database(char *database, char *table, char *set, char *where);
void delete_database(char *table, char *fill_table, char *where);
//end crud
#endif //UCHAT_SERVER_H