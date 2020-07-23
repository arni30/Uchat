#include "uchat_server.h"

void mx_res_js_get_message_history(t_clients *client, t_list *list) {
    t_json_data json = {.type = JS_MES_HIST, .status = 200};
    char *new_json = NULL;
    int len = mx_list_size(list);

    json.messages_arr = malloc(sizeof(t_message) * len / 5);
    for (int i = 0; list != NULL; i++) {
        json.messages_arr[i].message_id = mx_atoi(list->data);
        json.messages_arr[i].client1_id = mx_atoi(list->next->data);
        json.messages_arr[i].text = mx_strdup((list->next->next->data));
        json.messages_arr[i].delivery_time = mx_atoi(list->next->next->next->data);
        json.message.channel_id = mx_atoi(list->next->next->next->next->data);
        list = list->next->next->next->next->next;
    }
    json.messages_arr_size = len / 5;
    new_json = mx_json_make_json(JS_MES_HIST, &json);
    mx_logger("JSON write:",  new_json + 4);
    SSL_write(client->ssl, new_json, mx_strlen(new_json + 4) + 4);
    if(json.messages_arr != NULL)
        free(json.messages_arr);
    mx_strdel(&new_json);
}