#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

List list_new() {
    List list = memalloc(sizeof(*list));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_release(List list) {
    list_clear(list);
    free(list);
}

void list_full_release(List list, void (*release)(void *)) {
    list_full_clear(list, release);
    free(list);
}

int list_equals(List list1, List list2) {
    int list1_size = list_size(list1);
    if (list1_size == list_size(list2)) {
        for (int i = 0; i < list1_size; i++)
            if (list_at(list1, i) != list_at(list2, i))
                return 0;
        return 1;
    }
    return 0;
}

int list_equals_cmp(List list1, List list2, int (*cmp)(void *, void *)) {
    int list1_size = list_size(list1);
    if (list1_size == list_size(list2)) {
        for (int i = 0; i < list1_size; i++)
            if (cmp(list_at(list1, i), list_at(list2, i)) == 0)
                return 0;
        return 1;
    }
    return 0;
}

char *list_to_str(List list, char *(*to_str)(void *)) {
    List str_list = list_new();
    for (ListItem it = list_head(list); it; it = list_next(it)) {
        char *str = to_str(list_value(it));
        list_append(str_list, str_escape(str, ","));
        free(str);
    }
    char *str = str_join(str_list, ",");
    list_full_release(str_list, free);
    return str;
}

List list_from_str(char *str, void *(*from_str)(char *)) {
    List list = list_new();
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

List list_dup(List list) {
    List dup = list_new();
    for (ListItem it = list_head(list); it; it = list_next(it))
        list_append(dup, list_value(it));
    return dup;
}

ListItem list_get_head(List list) {
    return list->head;
}

void list_set_head(List list, ListItem head) {
    list->head = head;
}

ListItem list_get_tail(List list) {
    return list->tail;
}

void list_set_tail(List list, ListItem tail) {
    list->tail = tail;
}

ListItem list_prev(ListItem item) {
    return list_item_prev(item);
}

ListItem list_next(ListItem item) {
    return list_item_next(item);
}

void *list_value(ListItem item) {
    return list_item_value(item);
}

ListItem list_head(List list) {
    return list->head;
}

ListItem list_tail(List list) {
    return list->tail;
}

int list_size(List list) {
    int size = 0;
    for (ListItem it = list_head(list); it; it = list_next(it))
        size++;
    return size;
}

ListItem list_item_at(List list, int index) {
    if (index < 0) {
        for (ListItem it = list_tail(list); it; it = list_prev(it), index++)
            if (index == -1)
                return it;
    }
    else {
        for (ListItem it = list_head(list); it; it = list_next(it), index--)
            if (index == 0)
                return it;
    }
    return NULL;
}

void *list_at(List list, int index) {
    ListItem item = list_item_at(list, index);
    return (item) ? list_value(item) : NULL;
}

ListItem list_random_item(List list) {
    return (list->head) ? list_item_at(list, int_random(0, list_size(list) - 1))
                        : NULL;
}

void *list_random(List list) {
    return (list->head) ? list_value(list_random_item(list)) : NULL;
}

void list_insert_before_item(List list, void *value, ListItem next) {
    ListItem prev = (next) ? list_prev(next) : list->tail;
    ListItem item = list_item_new(value, prev, next);
    if (next == list->head)
        list->head = item;
    if (prev == list->tail)
        list->tail = item;
    if (prev)
        list_item_set_next(prev, item);
    if (next)
        list_item_set_prev(next, item);
}

void list_insert_after_item(List list, void *value, ListItem prev) {
    ListItem next = (prev) ? list_next(prev) : list->head;
    list_insert_before_item(list, value, next);
}

void list_insert(List list, void *value, int index) {
    ListItem item = list_item_at(list, index);
    if (index >= 0)
        list_insert_before_item(list, value, item);
    else
        list_insert_after_item(list, value, item);
}

void list_prepend(List list, void *value) {
    list_insert_after_item(list, value, NULL);
}

void list_append(List list, void *value) {
    list_insert_before_item(list, value, NULL);
}

void list_remove_item(List list, ListItem item) {
    ListItem prev = list_prev(item);
    ListItem next = list_next(item);
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

void list_remove_full_item(List list, ListItem item, void (*release)(void *)) {
    release(list_value(item));
    list_remove_item(list, item);
}

void list_remove_at(List list, int index) {
    ListItem item = list_item_at(list, index);
    list_remove_item(list, item);
}

void list_full_remove_at(List list, int index, void (*release)(void *)) {
    ListItem item = list_item_at(list, index);
    list_remove_full_item(list, item, release);
}

void list_remove(List list, void *value) {
    ListItem item = list_find(list, value);
    if (item)
        list_remove_item(list, item);
}

void list_full_remove(List list, void *value, void (*release)(void *)) {
    ListItem item = list_find(list, value);
    if (item)
        list_remove_full_item(list, item, release);
}

void list_remove_cmp(List list, int (*cmp)(void *, void *), void *value) {
    ListItem item = list_find_cmp(list, cmp, value);
    if (item)
        list_remove_item(list, item);
}

void list_full_remove_cmp(List list, int (*cmp)(void *, void *), void *value,
                          void (*release)(void *)) {
    ListItem item = list_find_cmp(list, cmp, value);
    if (item)
        list_remove_full_item(list, item, release);
}

void *list_pop_front(List list) {
    void *value = list_at(list, 0);
    if (list->head)
        list_remove_at(list, 0);
    return value;
}

void *list_pop_back(List list) {
    void *value = list_at(list, -1);
    if (list->head)
        list_remove_at(list, -1);
    return value;
}

void *list_pop_random(List list) {
    ListItem item = list_random_item(list);
    if (item) {
        void *value = list_value(item);
        list_remove_item(list, item);
        return value;
    }
    return NULL;
}

void list_clear(List list) {
    for (ListItem it = list_head(list), next; it; it = next) {
        next = it->next;
        list_item_release(it);
    }
    list->head = list->tail = NULL;
}

void list_full_clear(List list, void (*release)(void *)) {
    list_foreach(list, release);
    list_clear(list);
}

void list_extend(List list1, List list2) {
    for (ListItem it = list_head(list2); it; it = it->next)
        list_append(list1, list_value(it));
}

List list_map(List list, void *(*map)(void *)) {
    List mapped = list_new();
    for (ListItem it = list_head(list); it; it = list_next(it))
        list_append(mapped, map(list_value(it)));
    return mapped;
}

ListItem list_find(List list, void *value) {
    for (ListItem it = list_head(list); it; it = list_next(it))
        if (value == list_value(it))
            return it;
    return NULL;
}

ListItem list_find_cmp(List list, int (*cmp)(void *, void *), void *value) {
    for (ListItem it = list_head(list); it; it = list_next(it))
        if (cmp(list_value(it), value))
            return it;
    return NULL;
}

int list_index(List list, ListItem item) {
    int index = 0;
    for (ListItem it = list_head(list); it; it = list_next(it), index++)
        if (item == it)
            return index;
    return -1;
}

int list_min(List list, int (*func)(void *)) {
    int min = INT_MAX;
    for (ListItem it = list_head(list); it; it = list_next(it)) {
        int value = func(list_value(it));
        min = (value < min) ? value : min;
    }
    return min;
}

int list_max(List list, int (*func)(void *)) {
    int max = INT_MIN;
    for (ListItem it = list_head(list); it; it = list_next(it)) {
        int value = func(list_value(it));
        max = (value > max) ? value : max;
    }
    return max;
}

void list_reverse(List list) {
    for (ListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        list_item_set_next(it, list_prev(it));
        list_item_set_prev(it, next);
    }
    ListItem temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void list_foreach(List list, void (*func)(void *)) {
    for (ListItem it = list_head(list); it; it = list_next(it))
        func(list_value(it));
}

void list_filter(List list, int (*filter)(void *)) {
    for (ListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        if (filter(list_value(it)) == 0)
            list_remove_item(list, it);
    }
}

void list_full_filter(List list, int (*filter)(void *), void (*release)(void *)) {
    for (ListItem it = list_head(list), next; it; it = next) {
        next = list_next(it);
        if (filter(list_value(it)) == 0)
            list_remove_full_item(list, it, release);
    }
}

