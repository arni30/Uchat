#include "uchat_client.h"

static char *get_text_of_textview(GtkWidget *text_view)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
    gchar *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    gtk_text_buffer_delete(buffer, &start, &end);
    return text;
}

void mx_on_butSend_clicked(__attribute__((unused)) GtkWidget *button, gpointer data)
{
    t_mainWindowObjects *mwo = (t_mainWindowObjects *)data;
    GtkWidget *row;
    char *message = mx_handle_user_input(get_text_of_textview(mwo->entryMessage));
    if (!mx_validate_message(message, mwo->Window))
        return;
    char *json_str = NULL;
    t_json_data *json = calloc(1, sizeof(t_json_data));

    row = mx_create_message(message, mwo, 0); //change signal connectors
    gtk_list_box_insert(GTK_LIST_BOX(mwo->messageList), row, -1);
    gtk_widget_show_all(GTK_WIDGET(mwo->chatWindow));
    ///
    int user_ids1[3] = {1, 2, 3};
    t_channel channels[1] = {
            {.channel_id = 0,
                    .channel_name = "asdasdasdddsdsdas",
                    .user_ids = user_ids1,
                    .user_ids_size = 3,
                    .last_mes_time = 0}};
    json->type = JS_MES_OUT;
    json->message.text = strdup(message);
    json->user_id = mwo->user_id;
    json->new_channel = true;
    json->new_channel_data = channels[0];
    strcpy(json->token, mwo->token);
    json->message.client1_id = mwo->user_id;
    json->message.channel_id = 1;

    json_str = mx_json_make_json(JS_MES_OUT, json);
    if (SSL_connect(mwo->ssl) == -1) /* perform the connection */
        ERR_print_errors_fp(stderr);
    else
        SSL_write(mwo->ssl, json_str, mx_strlen(json_str + 4) + 4);
    mx_strdel(&json_str);
    mx_strdel(&json->message.text);
    free(json);
    g_free(message);
}