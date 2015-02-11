#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

ADTList list_new() {
    ADTList list = memalloc(sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_release(ADTList list) {
    list_clear(list);
    free(list);
}

void list_full_release(ADTList list, void (*release)(void *)) {
    list_full_clear(list, release);
    free(list);
}

int list_equals(ADTList list1, ADTList list2) {
    int list1_size = list_size(list1);
    if (list1_size == list_size(list2)) {
        for (int i = 0; i < list1_size; i++)
            if (list_at(list1, i) != list_at(list2, i))
                return 0;
        return 1;
    }
    return 0;
}

int list_equals_cmp(ADTList list1, ADTList list2, int (*cmp)(void *, void *)) {
    int list1_size = list_size(list1);
    if (list1_size == list_size(list2)) {
        for (int i = 0; i < list1_size; i++)
            if (cmp(list_at(list1, i), list_at(list2, i)) == 0)
                return 0;
        return 1;
    }
    return 0;
}

char *list_to_str(ADTList list, char *(*to_str)(void *)) {
    ADTList str_list = list_new();
    for (ADTListItem it = list_head(list); it; it = list_next(it)) {
        char *str = to_str(list_value(it));
        list_append(str_list, str_escape(str, ","));
        free(str);
    }
    char *str = str_join(str_list, ",");
    list_full_release(str_list, free);
    return str;
}

ADTList list_from_str(char *str, void *(*from_str)(char *)) {
    ADTList list = list_new();
    int len = strlen(str);
    for (int i = 0, escape = 0, start = 0; i <= len; i++) {
        if ((str[i] == ',' && !escape) || (i == len && len > 0)) {
            char *substr = str_substr(str, start, i - start);
            char *unescaped = str_unescape(substr);
            list_append(list, from_str(unescaped));
            start = i + 1;
            free(unescaped);
            free(substr);
        }
        if (str[i] == '\\' && !escape)
            escape = 1;
        else
            escape = 0;
    }
    return list;
}

ADTList list_dup(ADTList list) {
    ADTList dup = list_new();
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        list_append(dup, list_value(it));
    return dup;
}

ADTListItem list_get_head(ADTList list) {
    return list->head;
}

void list_set_head(ADTList list, ADTListItem head) {
    list->head = head;
}

ADTListItem list_get_tail(ADTList list) {
    return list->tail;
}

void list_set_tail(ADTList list, ADTListItem tail) {
    list->tail = tail;
}

ADTListItem list_prev(ADTListItem item) {
    return list_item_prev(item);
}

ADTListItem list_next(ADTListItem item) {
    return list_item_next(item);
}

void *list_value(ADTListItem item) {
    return list_item_value(item);
}

ADTListItem list_head(ADTList list) {
    return list->head;
}

ADTListItem list_tail(ADTList list) {
    return list->tail;
}

int list_size(ADTList list) {
    int size = 0;
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        size++;
    return size;
}

ADTListItem list_item_at(ADTList list, int index) {
    if (index < 0) {
        for (ADTListItem it = list_tail(list); it; it = list_prev(it), index++)
            if (index == -1)
                return it;
    }
    else {
        for (ADTListItem it = list_head(list); it; it = list_next(it), index--)
            if (index == 0)
                return it;
    }
    return NULL;
}

void *list_at(ADTList list, int index) {
    ADTListItem item = list_item_at(list, index);
    return (item) ? list_value(item) : NULL;
}

ADTListItem list_random_item(ADTList list) {
    return (list->head) ? list_item_at(list, int_random(0, list_size(list) - 1)) : NULL;
}

void *list_random(ADTList list) {
    return (list->head) ? list_value(list_random_item(list)) : NULL;
}

void list_insert_before_item(ADTList list, void *value, ADTListItem next) {
    ADTListItem prev = (next) ? list_prev(next) : list->tail;
    ADTListItem item = list_item_new(value, prev, next);
    if (next == list->head)
        list->head = item;
    if (prev == list->tail)
        list->tail = item;
    if (prev)
        list_item_set_next(prev, item);
    if (next)
        list_item_set_prev(next, item);
}

void list_insert_after_item(ADTList list, void *value, ADTListItem prev) {
    ADTListItem next = (prev) ? list_next(prev) : list->head;
    list_insert_before_item(list, value, next);
}

void list_insert(ADTList list, void *value, int index) {
    ADTListItem item = list_item_at(list, index);
    if (index >= 0)
        list_insert_before_item(list, value, item);
    else
        list_insert_after_item(list, value, item);
}

void list_prepend(ADTList list, void *value) {
    list_insert_after_item(list, value, NULL);
}

void list_append(ADTList list, void *value) {
    list_insert_before_item(list, value, NULL);
}

void list_remove_item(ADTList list, ADTListItem item) {
    ADTListItem prev = list_prev(item);
    ADTListItem next = list_next(item);
    if (prev)
        list_item_set_next(prev, next);
    if (next)
        list_item_set_prev(next, prev);
    if (item == list->head)
        list->head = next;
    if (item == list->tail)
        list->tail = prev;
    list_item_release(item);
}

void list_remove_full_item(ADTList list, ADTListItem item, void (*release)(void *)) {
    release(list_value(item));
    list_remove_item(list, item);
}

void list_remove_at(ADTList list, int index) {
    ADTListItem item = list_item_at(list, index);
    list_remove_item(list, item);
}

void list_full_remove_at(ADTList list, int index, void (*release)(void *)) {
    ADTListItem item = list_item_at(list, index);
    list_remove_full_item(list, item, release);
}

void list_remove(ADTList list, void *value) {
    ADTListItem item = list_find(list, value);
    if (item)
        list_remove_item(list, item);
}

void list_full_remove(ADTList list, void *value, void (*release)(void *)) {
    ADTListItem item = list_find(list, value);
    if (item)
        list_remove_full_item(list, item, release);
}

void list_remove_cmp(ADTList list, int (*cmp)(void *, void *), void *value) {
    ADTListItem item = list_find_cmp(list, cmp, value);
    if (item)
        list_remove_item(list, item);
}

void list_full_remove_cmp(ADTList list, int (*cmp)(void *, void *), void *value,
                          void (*release)(void *)) {
    ADTListItem item = list_find_cmp(list, cmp, value);
    if (item)
        list_remove_full_item(list, item, release);
}

void *list_pop_front(ADTList list) {
    void *value = list_at(list, 0);
    if (list->head)
        list_remove_at(list, 0);
    return value;
}

void *list_pop_back(ADTList list) {
    void *value = list_at(list, -1);
    if (list->head)
        list_remove_at(list, -1);
    return value;
}

void *list_pop_random(ADTList list) {
    ADTListItem item = list_random_item(list);
    if (item) {
        void *value = list_value(item);
        list_remove_item(list, item);
        return value;
    }
    return NULL;
}

void list_clear(ADTList list) {
    for (ADTListItem it = list_head(list), next; it; it = next) {
        next = it->next;
        list_item_release(it);
    }
    list->head = list->tail = NULL;
}

void list_full_clear(ADTList list, void (*release)(void *)) {
    list_foreach(list, release);
    list_clear(list);
}

void list_extend(ADTList list1, ADTList list2) {
    for (ADTListItem it = list_head(list2); it; it = it->next)
        list_append(list1, list_value(it));
}

ADTList list_map(ADTList list, void *(*map)(void *)) {
    ADTList mapped = list_new();
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        list_append(mapped, map(list_value(it)));
    return mapped;
}

ADTListItem list_find(ADTList list, void *value) {
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        if (value == list_value(it))
            return it;
    return NULL;
}

ADTListItem list_find_cmp(ADTList list, int (*cmp)(void *, void *), void *value) {
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        if (cmp(list_value(it), value))
            return it;
    return NULL;
}

int list_index(ADTList list, ADTListItem item) {
    int index = 0;
    for (ADTListItem it = list_head(list); it; it = list_next(it), index++)
        if (item == it)
            return index;
    return -1;
}

int list_min(ADTList list, int (*func)(void *)) {
    int min = INT_MAX;
    for (ADTListItem it = list_head(list); it; it = list_next(it)) {
        int value = func(list_value(it));
        min = (value < min) ? value : min;
    }
    return min;
}

int list_max(ADTList list, int (*func)(void *)) {
    int max = INT_MIN;
    for (ADTListItem it = list_head(list); it; it = list_next(it)) {
        int value = func(list_value(it));
        max = (value > max) ? value : max;
    }
    return max;
}

void list_reverse(ADTList list) {
    for (ADTListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        list_item_set_next(it, list_prev(it));
        list_item_set_prev(it, next);
    }
    ADTListItem temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void list_foreach(ADTList list, void (*func)(void *)) {
    for (ADTListItem it = list_head(list); it; it = list_next(it))
        func(list_value(it));
}

void list_filter(ADTList list, int (*filter)(void *)) {
    for (ADTListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        if (filter(list_value(it)) == 0)
            list_remove_item(list, it);
    }
}

void list_full_filter(ADTList list, int (*filter)(void *), void (*release)(void *)) {
    for (ADTListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        if (filter(list_value(it)) == 0)
            list_remove_full_item(list, it, release);
    }
}

