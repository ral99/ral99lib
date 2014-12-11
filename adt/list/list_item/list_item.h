#ifndef __ADT__LIST__LIST_ITEM__
#define __ADT__LIST__LIST_ITEM__

typedef struct ListItem *ListItem;
struct ListItem {
    ListItem prev, next;
    void *value;
};

/* Return a new item. */
ListItem list_item_new(void *value, ListItem prev, ListItem next);

/* Free the memory used by item. */
void list_item_release(ListItem item);

/* Free the memory used by item and call release on its value. */
void list_item_full_release(ListItem item, void (*release)(void *));

/* Getter method for prev. */
ListItem list_item_get_prev(ListItem item);

/* Setter method for prev. */
void list_item_set_prev(ListItem item, ListItem prev);

/* Getter method for next. */
ListItem list_item_get_next(ListItem item);

/* Setter method for next. */
void list_item_set_next(ListItem item, ListItem next);

/* Getter method for value. */
void *list_item_get_value(ListItem item);

/* Setter method for value. */
void list_item_set_value(ListItem item, void *value);

/* Boolean method for prev. */
int list_item_prev_is(ListItem item, ListItem prev);

/* Boolean method for next. */
int list_item_next_is(ListItem item, ListItem next);

/* Boolean method for value. */
int list_item_value_is(ListItem item, void *value);

/* Return the previous item. */
ListItem list_item_prev(ListItem prev);

/* Return the next item. */
ListItem list_item_next(ListItem item);

/* Return the item value. */
void *list_item_value(ListItem item);

#endif

