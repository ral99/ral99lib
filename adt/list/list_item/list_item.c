#include <stdlib.h>

#include "adt/adt.h"
#include "mem/mem.h"

ListItem list_item_new(void *value, ListItem prev, ListItem next) {
    ListItem item = memalloc(sizeof(*item));
    item->value = value;
    item->prev = prev;
    item->next = next;
    return item;
}

void list_item_release(ListItem item) {
    free(item);
}

void list_item_full_release(ListItem item, void (*release)(void *)) {
    release(item->value);
    list_item_release(item);
}

ListItem list_item_get_prev(ListItem item) {
    return item->prev;
}

void list_item_set_prev(ListItem item, ListItem prev) {
    item->prev = prev;
}

ListItem list_item_get_next(ListItem item) {
    return item->next;
}

void list_item_set_next(ListItem item, ListItem next) {
    item->next = next;
}

void *list_item_get_value(ListItem item) {
    return item->value;
}

void list_item_set_value(ListItem item, void *value) {
    item->value = value;
}

int list_item_prev_is(ListItem item, ListItem prev) {
    return (list_item_prev(item) == prev) ? 1 : 0;
}

int list_item_next_is(ListItem item, ListItem next) {
    return (list_item_next(item) == next) ? 1 : 0;
}

int list_item_value_is(ListItem item, void *value) {
    return (list_item_value(item) == value) ? 1 : 0;
}

ListItem list_item_prev(ListItem item) {
    return item->prev;
}

ListItem list_item_next(ListItem item) {
    return item->next;
}

void *list_item_value(ListItem item) {
    return item->value;
}

