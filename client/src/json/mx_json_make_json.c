#include "uchat_client.h"

char *mx_json_make_json(enum e_json_types type, t_json_data *data) {
    char *(*fn_p[JS_NUM])(t_json_data *) = {mx_json_register_request,
                                            mx_json_log_in_request,
                                            mx_json_log_out_request,
                                            mx_json_message_delete_in_response,
                                            mx_json_message_delete_out_request,
                                            mx_json_message_edit_in_response,
                                            mx_json_message_edit_out_request,
                                            mx_json_message_in_response,
                                            mx_json_message_out_request};

    return fn_p[type](data);
}