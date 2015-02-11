#ifndef __ADT__LIST__LIST__
#define __ADT__LIST__LIST__

#include "adt/adt.h"

typedef struct _ADTList *ADTList;
struct _ADTList {
    ADTListItem head, tail;
};

/* Return a new list. */
ADTList list_new();

/* Free the memory used by list. */
void list_release(ADTList list);

/* Free the memory used by list and call release on its values. */
void list_full_release(ADTList list, void (*release)(void *));

/* Return 1 if the values of the lists are equal. 0, otherwise. */
int list_equals(ADTList list1, ADTList list2);

/* Return 1 if the values of the lists are equal compared with cmp. 0, otherwise. */
int list_equals_cmp(ADTList list1, ADTList list2, int (*cmp)(void *, void *));

/* Return the string representation of the list. */
char *list_to_str(ADTList list, char *(*to_str)(void *));

/* Return list from its string representation. */
ADTList list_from_str(char *string, void *(*from_str)(char *));

/* Return the duplicated list. */
ADTList list_dup(ADTList list);

/* Getter method for head. */
ADTListItem list_get_head(ADTList list);

/* Setter method for head. */
void list_set_head(ADTList list, ADTListItem head);

/* Getter method for tail. */
ADTListItem list_get_tail(ADTList list);

/* Setter method for tail. */
void list_set_tail(ADTList list, ADTListItem tail);

/* Return the previous item. */
ADTListItem list_prev(ADTListItem item);

/* Return the next item. */
ADTListItem list_next(ADTListItem item);

/* Return the item value. */
void *list_value(ADTListItem item);

/* Return the item at the start of the list. */
ADTListItem list_head(ADTList list);

/* Return the item at the end of the list. */
ADTListItem list_tail(ADTList list);

/* Return the size of the list. */
int list_size(ADTList list);

/* Return the item at position index or NULL. */
ADTListItem list_item_at(ADTList list, int index);

/* Return the value at position index or NULL. */
void *list_at(ADTList list, int index);

/* Return an item at a random position or NULL. */
ADTListItem list_random_item(ADTList list);

/* Return a value at a random position or NULL. */
void *list_random(ADTList list);

/* Insert value before item. */
void list_insert_before_item(ADTList list, void *value, ADTListItem next);

/* Insert value after item. */
void list_insert_after_item(ADTList list, void *value, ADTListItem prev);

/* Insert value at position index. If the absolute value of index is larger than the
 * list length, insert value on to the tail of the list, if index is positive, or on
 * to the head of the list, if index is negative. */
void list_insert(ADTList list, void *value, int index);

/* Insert value on to the head of the list. */
void list_prepend(ADTList list, void *value);

/* Insert value on to the tail of the list. */
void list_append(ADTList list, void *value);

/* Remove the item from the list. */
void list_remove_item(ADTList list, ADTListItem item);

/* Remove the item from the list and call release on its value. */
void list_remove_full_item(ADTList list, ADTListItem item, void (*release)(void *));

/* Remove the value at position index. */
void list_remove_at(ADTList list, int index);

/* Remove and release the value at position index. */
void list_full_remove_at(ADTList list, int index, void (*release)(void *));

/* Remove the first occurence of value. */
void list_remove(ADTList list, void *value);

/* Remove and release the first occurence of value. */
void list_full_remove(ADTList list, void *value, void (*release)(void *));

/* Remove the first occurence of value compared with cmp. */
void list_remove_cmp(ADTList list, int (*cmp)(void *, void *), void *value);

/* Remove and release the first occurence of value compared with cmp. */
void list_full_remove_cmp(ADTList list, int (*cmp)(void *, void *), void *value,
                          void (*release)(void *));

/* Return and remove the value at the start or NULL. */
void *list_pop_front(ADTList list);

/* Return and remove the value at the end or NULL. */
void *list_pop_back(ADTList list);

/* Return and remove a value at a random position or NULL. */
void *list_pop_random(ADTList list);

/* Clear the list. */
void list_clear(ADTList list);

/* Clear the list and release its values. */
void list_full_clear(ADTList list, void (*release)(void *));

/* Extend list1 by appending values from list2. */
void list_extend(ADTList list1, ADTList list2);

/* Return the list of mapped values. */
ADTList list_map(ADTList list, void *(*map)(void *));

/* Return an item with the specified value or NULL. */
ADTListItem list_find(ADTList list, void *value);

/* Return an item with the specified value compared with cmp or NULL. */
ADTListItem list_find_cmp(ADTList list, int (*cmp)(void *, void*), void *value);

/* Return the index of the item in list or -1. */
int list_index(ADTList list, ADTListItem item);

/* Return the minimun func value for the list. */
int list_min(ADTList list, int (*func)(void *));

/* Return the maximum func value for the list. */
int list_max(ADTList list, int (*func)(void *));

/* Reverse the list order. */
void list_reverse(ADTList list);

/* Call func on each value of the list. */
void list_foreach(ADTList list, void (*func)(void *));

/* Remove from the list the values which filter return 0. */
void list_filter(ADTList list, int (*filter)(void *));

/* Remove from the list and release the values which filter return 0. */
void list_full_filter(ADTList list, int (*filter)(void *), void (*release)(void *));

#endif

