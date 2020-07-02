#include "../../inc/header.h"

char *mx_json_message_delete_out_request(t_json_data *data) {
    char *s;
    int len = asprintf(&s, "0000" MX_REQ_MES_DEL_OUT, JS_MES_DEL_OUT, data->message.message_id,
             data->message.client1_id, data->token);
    *(int *)s = len;

    return s;
}

char *mx_json_message_delete_out_response(t_json_data *data) {
    char *s;
    int len = asprintf(&s, "0000" MX_RESP_MES_DEL_OUT, JS_MES_DEL_OUT, data->status,
             data->message.message_id);
    *(int *)s = len;

    return s;
}
