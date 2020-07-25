#include "uchat_client.h"
void mx_set_chat_component(t_mainWindowObjects *mwo) {
    GList *children, *iter;

    children = gtk_container_get_children(GTK_CONTAINER(gtk_builder_get_object(mwo->builder, "scrolled_chat")));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_container_remove(GTK_CONTAINER(mwo->viewPort), GTK_WIDGET(iter->data));
    }
//    gtk_box_pack_start(GTK_BOX(gtk_builder_get_object(mwo->builder, "gtkbox")), gtk_component, TRUE, TRUE, 5);
    gtk_widget_show_all(GTK_WIDGET(mwo->Window));

    // g_list_free(children);
}

void mx_onBack_to_chats(__attribute__((unused)) GtkWidget *button, gpointer data)
{
    //почистить текстовый буфер
    t_mainWindowObjects *mwo = (t_mainWindowObjects *)data;
//    if (mwo->curr_chatWindow)
//        g_object_unref(&mwo->curr_chatWindow);
//    if (mwo->curr_messageList)
//        g_object_unref(&mwo->curr_messageList);
    //gtk_widget_hide(mwo->curr_channel_info->messageList);
//    if (mwo->curr_channel_info) {
//        free(mwo->curr_channel_info);
//        mwo->curr_channel_info = NULL;
//    }
    mwo->channel_info = mwo->channel_info->first;
    //if (mwo->channel_info != NULL) {
    while (mwo->channel_info != NULL && mwo->channel_info->chat_button != NULL) {
        if (mwo->channel_info->channel_data.channel_id ==
                mwo->curr_channel_info->channel_data.channel_id) {
            break;
        }
        mwo->channel_info = mwo->channel_info->next;
    }
    mwo->channel_info->messageList = g_object_ref(mwo->curr_channel_info->messageList);
    gtk_container_remove(GTK_CONTAINER(mwo->viewPort), mwo->curr_channel_info->messageList);
    mx_set_component(mwo, mwo->mainWindow);
    //mx_set_chat_component(mwo);
}

void mx_on_butAddchat(__attribute__((unused)) GtkWidget *button, gpointer data)
{ //создавать новое диалоговое окно
    GtkBuilder *builder;
    GError *error = NULL;
    t_mainWindowObjects *mwo = (t_mainWindowObjects *)data;
    char *json_str = NULL;
    //GtkWidget *addChat_Dialog;
    if (mwo->add_chat == 0) {
        mwo->add_chat = 1;
        t_json_data json = {.user_id = mwo->user_id, .type = JS_GET_USERS};
        strcpy(json.token, mwo->token);
        json_str = mx_json_make_json(JS_GET_USERS, &json);
        mx_printstr(json_str + 4);
        SSL_write(mwo->ssl, json_str, mx_strlen(json_str + 4) + 4);
        mx_strdel(&json_str);
        puts("GET_USERS");

        builder = gtk_builder_new();
//    gtk_style_context_add_provider_for_screen (gdk_screen_get_default(),
//                                               GTK_STYLE_PROVIDER(mainObjects->provider),
//                                               GTK_STYLE_PROVIDER_PRIORITY_USER);
        if (!gtk_builder_add_from_file(builder, "sent_gui.glade", &error)) {
            mx_printstr(error->message);
        }
        mwo->addChat_Dialog = GTK_WIDGET(
                gtk_builder_get_object(builder, "dialog_add_chat"));
        mwo->entryChatName = GTK_ENTRY(
                gtk_builder_get_object(builder, "entry_chat_name"));
        mwo->entryChatUsers = GTK_ENTRY(gtk_builder_get_object(builder, "entry_user_chat"));

        mwo->usersList = gtk_list_box_new();
        gtk_list_box_set_selection_mode(GTK_LIST_BOX(mwo->usersList),
                                        GTK_SELECTION_NONE);
        gtk_builder_connect_signals(builder, mwo);
        gtk_container_add(GTK_CONTAINER(
                gtk_builder_get_object(builder, "scrolled_window_chatUsers")),
                          mwo->usersList);
        gtk_window_set_transient_for(GTK_WINDOW(mwo->addChat_Dialog),
                                     mwo->Window);
        gtk_window_set_position(GTK_WINDOW(mwo->addChat_Dialog),
                                GTK_WIN_POS_CENTER_ON_PARENT);
        //обработать ответ от сервера с логинами в reciever
        gtk_widget_show_all(GTK_WIDGET(mwo->addChat_Dialog));
        //gtk_dialog_run(GTK_DIALOG(mwo->addChat_Dialog));
    }
}
