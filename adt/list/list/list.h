#ifndef __ADT__LIST__LIST__
#define __ADT__LIST__LIST__

#include "adt/list/list_item/list_item.h"

typedef struct List *List;
struct List {
    ListItem head, tail;
};

/* Return a new list. */
List list_new();

/* Free the memory used by list. */
void list_release(List list);

/* Free the memory used by list and call release on its values. */
void list_full_release(List list, void (*release)(void *));

/* Return 1 if the values of the lists are equal. 0, otherwise. */
int list_equals(List list1, List list2);

/* Return 1 if the values of the lists are equal compared with cmp. 0, otherwise. */
int list_equals_cmp(List list1, List list2, int (*cmp)(void *, void *));

/* Return the string representation of the list. */
char *list_to_str(List list, char *(*to_str)(void *));

/* Return list from its string representation. */
List list_from_str(char *string, void *(*from_str)(char *));

/* Return the duplicated list. */
List list_dup(List list);

/* Getter method for head. */
ListItem list_get_head(List list);

/* Setter method for head. */
void list_set_head(List list, ListItem head);

/* Getter method for tail. */
ListItem list_get_tail(List list);

/* Setter method for tail. */
void list_set_tail(List list, ListItem tail);

/* Return the previous item. */
ListItem list_prev(ListItem item);

/* Return the next item. */
ListItem list_next(ListItem item);

/* Return the item value. */
void *list_value(ListItem item);

/* Return the item at the start of the list. */
ListItem list_head(List list);

/* Return the item at the end of the list. */
ListItem list_tail(List list);

/* Return the size of the list. */
int list_size(List list);

/* Return the item at position index or NULL. */
ListItem list_item_at(List list, int index);

/* Return the value at position index or NULL. */
void *list_at(List list, int index);

/* Return an item at a random position or NULL. */
ListItem list_random_item(List list);

/* Return a value at a random position or NULL. */
void *list_random(List list);

/* Insert value before item. */
void list_insert_before_item(List list, void *value, ListItem next);

/* Insert value after item. */
void list_insert_after_item(List list, void *value, ListItem prev);

/* Insert value at position index. If the absolute value of index is larger than the
 * list length, insert value on to the tail of the list, if index is positive, or on
 * to the head of the list, if index is negative. */
void list_insert(List list, void *value, int index);

/* Insert value on to the head of the list. */
void list_prepend(List list, void *value);

/* Insert value on to the tail of the list. */
void list_append(List list, void *value);

/* Remove the item from the list. */
void list_remove_item(List list, ListItem item);

/* Remove the item from the list and call release on its value. */
void list_remove_full_item(List list, ListItem item, void (*release)(void *));

/* Remove the value at position index. */
void list_remove_at(List list, int index);

/* Remove and release the value at position index. */
void list_full_remove_at(List list, int index, void (*release)(void *));

/* Remove the first occurence of value. */
void list_remove(List list, void *value);

/* Remove and release the first occurence of value. */
void list_full_remove(List list, void *value, void (*release)(void *));

/* Remove the first occurence of value compared with cmp. */
void list_remove_cmp(List list, int (*cmp)(void *, void *), void *value);

/* Remove and release the first occurence of value compared with cmp. */
void list_full_remove_cmp(List list, int (*cmp)(void *, void *), void *value,
                          void (*release)(void *));

/* Return and remove the value at the start or NULL. */
void *list_pop_front(List list);

/* Return and remove the value at the end or NULL. */
void *list_pop_back(List list);

/* Return and remove a value at a random position or NULL. */
void *list_pop_random(List list);

/* Clear the list. */
void list_clear(List list);

/* Clear the list and release its values. */
void list_full_clear(List list, void (*release)(void *));

/* Extend list1 by appending values from list2. */
void list_extend(List list1, List list2);

/* Return the list of mapped values. */
List list_map(List list, void *(*map)(void *));

/* Return an item with the specified value or NULL. */
ListItem list_find(List list, void *value);

/* Return an item with the specified value compared with cmp or NULL. */
ListItem list_find_cmp(List list, int (*cmp)(void *, void*), void *value);

/* Return the index of the item in list or -1. */
int list_index(List list, ListItem item);

/* Return the minimun func value for the list. */
int list_min(List list, int (*func)(void *));

/* Return the maximum func value for the list. */
int list_max(List list, int (*func)(void *));

/* Reverse the list order. */
void list_reverse(List list);

/* Call func on each value of the list. */
void list_foreach(List list, void (*func)(void *));

/* Remove from the list the values which filter return 0. */
void list_filter(List list, int (*filter)(void *));

/* Remove from the list and release the values which filter return 0. */
void list_full_filter(List list, int (*filter)(void *), void (*release)(void *));

#endif

