#include "uchat_client.h"

int main(int argc, char **argv) {
    t_mainWindowObjects mainObjects;
    SSL_CTX *ctx;
    mainObjects.curr_chat_users = NULL;
    mainObjects.curr_chat = NULL;
    mainObjects.curr_channel_info = NULL;
    mainObjects.curr_messageList = NULL;
    mainObjects.user_ids = NULL;
    mainObjects.channel_info = malloc(sizeof(t_channel_info));
    mainObjects.channel_info->first = mainObjects.channel_info;
    mainObjects.channel_info->next = NULL;
    mainObjects.channel_info->chat_button = NULL;
    /* Init GTK+ */
    gtk_init(&argc, &argv);

    if (argc != 3) {
        mx_printerr("uchat_server: error args\n");
        mx_printerr("example: ./uchat ip port\n");
        exit(1);
    }
    SSL_library_init();
    ctx = mx_init_ctx();
    mainObjects.fd = mx_open_connection(argv[1], atoi(argv[2]));
    mainObjects.ssl = SSL_new(ctx);
    mx_show_certs(mainObjects.ssl);
    SSL_set_fd(mainObjects.ssl, mainObjects.fd);
    mx_create_login_window(&mainObjects);
}
