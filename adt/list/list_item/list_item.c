#include <stdlib.h>

#include "adt/adt.h"
#include "mem/mem.h"

ADTListItem list_item_new(void *value, ADTListItem prev, ADTListItem next) {
    ADTListItem item = (ADTListItem) memalloc(sizeof(*item));
    item->value = value;
    item->prev = prev;
    item->next = next;
    return item;
}

void list_item_release(ADTListItem item) {
    free(item);
}

void list_item_full_release(ADTListItem item, void (*release)(void *)) {
    release(item->value);
    list_item_release(item);
}

ADTListItem list_item_get_prev(ADTListItem item) {
    return item->prev;
}

void list_item_set_prev(ADTListItem item, ADTListItem prev) {
    item->prev = prev;
}

ADTListItem list_item_get_next(ADTListItem item) {
    return item->next;
}

void list_item_set_next(ADTListItem item, ADTListItem next) {
    item->next = next;
}

void *list_item_get_value(ADTListItem item) {
    return item->value;
}

void list_item_set_value(ADTListItem item, void *value) {
    item->value = value;
}

int list_item_prev_is(ADTListItem item, ADTListItem prev) {
    return (list_item_prev(item) == prev) ? 1 : 0;
}

int list_item_next_is(ADTListItem item, ADTListItem next) {
    return (list_item_next(item) == next) ? 1 : 0;
}

int list_item_value_is(ADTListItem item, void *value) {
    return (list_item_value(item) == value) ? 1 : 0;
}

ADTListItem list_item_prev(ADTListItem item) {
    return item->prev;
}

ADTListItem list_item_next(ADTListItem item) {
    return item->next;
}

void *list_item_value(ADTListItem item) {
    return item->value;
}

