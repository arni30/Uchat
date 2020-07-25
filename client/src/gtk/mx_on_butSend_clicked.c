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
    char *message = mx_handle_user_input(get_text_of_textview(mwo->entryMessage));
    if (!mx_validate_message(message, mwo->Window))
        return;
    char *json_str = NULL;
    t_json_data *json = calloc(1, sizeof(t_json_data));

    ///
    mwo->curr_message = mx_strdup(message);
    if (mwo->curr_chat_users != NULL && mwo->curr_chat != NULL) {
        t_channel channels[1] = {{
                        .channel_id = -1,
                        .user_ids_size = mx_arrlen(mwo->curr_chat_users) + 1,
                        .last_mes_time = 0}};
        strcpy(channels->channel_name, mwo->curr_chat);
        channels->user_ids = malloc(sizeof(int) * channels->user_ids_size);
        for (int i = 0; i < channels->user_ids_size; i++) {
            channels->user_ids[i] = mwo->user_ids[i];
            puts("\nuser   ");
            mx_printint(channels->user_ids[i]);
        }
        json->message.channel_id = -1;
        json->new_channel_data = channels[0];
        json->new_channel = true;
    }
    else {
        mwo->channel_info = mwo->channel_info->first;
        if (mwo->channel_info) {
            while (mwo->channel_info->next != NULL) {
                if (mwo->channel_info->channel_data.channel_id ==
                        mwo->curr_channel_info->channel_data.channel_id)
                    break;
                mwo->channel_info = mwo->channel_info->next;
            }
        }
        json->message.channel_id = mwo->channel_info->channel_data.channel_id;
    }
    json->type = JS_MES_OUT;
    json->message.text = strdup(message);
    json->user_id = mwo->user_id;
    //json->new_channel = false;
    strcpy(json->token, mwo->token);
    json->message.client1_id = mwo->user_id;

    json_str = mx_json_make_json(JS_MES_OUT, json);
    mx_printstr(json_str + 4);
    if (SSL_connect(mwo->ssl) == -1) /* perform the connection */
        ERR_print_errors_fp(stderr);
    else
        SSL_write(mwo->ssl, json_str, *(int *)json_str + 4);
    mx_strdel(&json_str);
    mx_strdel(&json->message.text);
    free(json);
    g_free(message);
}
