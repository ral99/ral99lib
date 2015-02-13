#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "str/str.h"

NETMessage message_new(char *id, char *text) {
    NETMessage message = (NETMessage) memalloc(sizeof(*message));
    message->id = str_dup(id);
    message->text = str_dup(text);
    return message;
}

void message_release(NETMessage message) {
    free(message->id);
    free(message->text);
    free(message);
}

int message_equals(NETMessage message1, NETMessage message2) {
    return (str_equals(message1->id, message2->id) &&
            str_equals(message1->text, message2->text)) ? 1 : 0;
}

char *message_to_str(NETMessage message) {
    ADTList message_list = list_new();
    list_append(message_list, message->id);
    list_append(message_list, message->text);
    char *str = list_to_str(message_list, (char *(*)(void *)) str_dup);
    list_release(message_list);
    return str;
}

NETMessage message_from_str(char *str) {
    ADTList message_list = list_from_str(str, (void *(*)(char *)) str_dup);
    NETMessage message = message_new((char *) list_at(message_list, 0),
                                     (char *) list_at(message_list, 1));
    list_full_release(message_list, free);
    return message;
}

NETMessage message_dup(NETMessage message) {
    return message_new(message->id, message->text);
}

char *message_get_id(NETMessage message) {
    return message->id;
}

void message_set_id(NETMessage message, char *id) {
    message->id = id;
}

char *message_get_text(NETMessage message) {
    return message->text;
}

void message_set_text(NETMessage message, char *text) {
    message->text = text;
}

int message_id_is(NETMessage message, char *id) {
    return str_equals(message->id, id);
}

int message_text_is(NETMessage message, char *text) {
    return str_equals(message->text, text);
}

char *message_id(NETMessage message) {
    return str_dup(message->id);
}

char *message_text(NETMessage message) {
    return str_dup(message->text);
}

