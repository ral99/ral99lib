#include <stdlib.h>

#include "net/message/message.h"
#include "util/util.h"
#include "adt/adt.h"

Message message_new(char *id, char *text) {
    Message message = memalloc(sizeof(*message));
    message->id = str_dup(id);
    message->text = str_dup(text);
    return message;
}

void message_release(Message message) {
    free(message->id);
    free(message->text);
    free(message);
}

int message_equals(Message message1, Message message2) {
    return (str_equals(message1->id, message2->id) &&
            str_equals(message1->text, message2->text)) ? 1 : 0;
}

char *message_to_str(Message message) {
    List message_list = list_new();
    list_append(message_list, message->id);
    list_append(message_list, message->text);
    char *str = list_to_str(message_list, (char *(*)(void *)) str_dup);
    list_release(message_list);
    return str;
}

Message message_from_str(char *str) {
    List message_list = list_from_str(str, (void *(*)(char *)) str_dup);
    Message message = message_new(list_at(message_list, 0),
                                  list_at(message_list, 1));
    list_full_release(message_list, free);
    return message;
}

Message message_dup(Message message) {
    return message_new(message->id, message->text);
}

char *message_get_id(Message message) {
    return message->id;
}

void message_set_id(Message message, char *id) {
    message->id = id;
}

char *message_get_text(Message message) {
    return message->text;
}

void message_set_text(Message message, char *text) {
    message->text = text;
}

int message_id_is(Message message, char *id) {
    return str_equals(message->id, id);
}

int message_text_is(Message message, char *text) {
    return str_equals(message->text, text);
}

char *message_id(Message message) {
    return str_dup(message->id);
}

char *message_text(Message message) {
    return str_dup(message->text);
}

