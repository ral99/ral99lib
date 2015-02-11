#ifndef __ADT__LIST__LIST_ITEM__
#define __ADT__LIST__LIST_ITEM__

typedef struct _ADTListItem *ADTListItem;
struct _ADTListItem {
    ADTListItem prev, next;
    void *value;
};

/* Return a new item. */
ADTListItem list_item_new(void *value, ADTListItem prev, ADTListItem next);

/* Free the memory used by item. */
void list_item_release(ADTListItem item);

/* Free the memory used by item and call release on its value. */
void list_item_full_release(ADTListItem item, void (*release)(void *));

/* Getter method for prev. */
ADTListItem list_item_get_prev(ADTListItem item);

/* Setter method for prev. */
void list_item_set_prev(ADTListItem item, ADTListItem prev);

/* Getter method for next. */
ADTListItem list_item_get_next(ADTListItem item);

/* Setter method for next. */
void list_item_set_next(ADTListItem item, ADTListItem next);

/* Getter method for value. */
void *list_item_get_value(ADTListItem item);

/* Setter method for value. */
void list_item_set_value(ADTListItem item, void *value);

/* Boolean method for prev. */
int list_item_prev_is(ADTListItem item, ADTListItem prev);

/* Boolean method for next. */
int list_item_next_is(ADTListItem item, ADTListItem next);

/* Boolean method for value. */
int list_item_value_is(ADTListItem item, void *value);

/* Return the previous item. */
ADTListItem list_item_prev(ADTListItem prev);

/* Return the next item. */
ADTListItem list_item_next(ADTListItem item);

/* Return the item value. */
void *list_item_value(ADTListItem item);

#endif

