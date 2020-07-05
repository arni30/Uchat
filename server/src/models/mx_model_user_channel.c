#include "uchat_server.h"

char *mx_model_user_channel_database(void) {
    return "sqlite3";
}

char *mx_model_user_channel_name_table(void) {
    return "delivery_user";
}

char **mx_model_user_channel_fill_table(void) {
    char **fill_table = malloc(sizeof(char*) * 7);

    fill_table[0] = mx_strdup("first_name");
    fill_table[1] = mx_strdup("last_name");
    fill_table[2] = mx_strdup("login");
    fill_table[3] = mx_strdup("password");
    fill_table[4] = mx_strdup("token");
    fill_table[5] = mx_strdup("create_at");
    fill_table[6] = NULL;
    return fill_table;
}

