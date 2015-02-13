#include <glib.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "adt/adt.h"
#include "str/str.h"

static void test_list_new_1() {
    ADTList list = list_new();
    g_assert(list != NULL);
    g_assert(list->head == NULL);
    g_assert(list->tail == NULL);
    list_release(list);
}

static void test_list_release_1() {
    ADTList list = list_new();
    list_release(list);
}

static void test_list_release_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_release(list);
}

static void test_list_full_release_1() {
    ADTList list = list_new();
    list_full_release(list, free);
}

static void test_list_full_release_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "def"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) "ghi"), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_release(list, free);
}

static void test_list_equals_1() {
    ADTList list1 = list_new();
    ADTList list2 = list_new();
    g_assert_cmpint(list_equals(list1, list2), ==, 1);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_2() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new(value1, NULL, NULL);
    ADTListItem list12 = list_item_new(value2, NULL, NULL);
    ADTListItem list13 = list_item_new(value3, NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new(value1, NULL, NULL);
    ADTListItem list22 = list_item_new(value2, NULL, NULL);
    ADTListItem list23 = list_item_new(value3, NULL, NULL);
    list2->head = list21;
    list2->tail = list23;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    g_assert_cmpint(list_equals(list1, list2), ==, 1);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_3() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new(value1, NULL, NULL);
    ADTListItem list12 = list_item_new(value2, NULL, NULL);
    ADTListItem list13 = list_item_new(value3, NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new(value3, NULL, NULL);
    ADTListItem list22 = list_item_new(value2, NULL, NULL);
    ADTListItem list23 = list_item_new(value1, NULL, NULL);
    list2->head = list21;
    list2->tail = list23;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    g_assert_cmpint(list_equals(list1, list2), ==, 0);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_4() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    char *value4 = (char *) "jkl";
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new(value1, NULL, NULL);
    ADTListItem list12 = list_item_new(value2, NULL, NULL);
    ADTListItem list13 = list_item_new(value3, NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new(value1, NULL, NULL);
    ADTListItem list22 = list_item_new(value2, NULL, NULL);
    ADTListItem list23 = list_item_new(value3, NULL, NULL);
    ADTListItem list24 = list_item_new(value4, NULL, NULL);
    list2->head = list21;
    list2->tail = list24;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_next(list23, list24);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    list_item_set_prev(list24, list23);
    g_assert_cmpint(list_equals(list1, list2), ==, 0);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_cmp_1() {
    ADTList list1 = list_new();
    ADTList list2 = list_new();
    g_assert_cmpint(list_equals_cmp(list1, list2, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_cmp_2() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list12 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list13 = list_item_new((char *) "ghi", NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list22 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list23 = list_item_new((char *) "ghi", NULL, NULL);
    list2->head = list21;
    list2->tail = list23;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    g_assert_cmpint(list_equals_cmp(list1, list2, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_cmp_3() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list12 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list13 = list_item_new((char *) "ghi", NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "ghi", NULL, NULL);
    ADTListItem list22 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list23 = list_item_new((char *) "abc", NULL, NULL);
    list2->head = list21;
    list2->tail = list23;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    g_assert_cmpint(list_equals_cmp(list1, list2, (int (*)(void *, void *)) str_equals), ==,
                    0);
    list_release(list1);
    list_release(list2);
}

static void test_list_equals_cmp_4() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list12 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list13 = list_item_new((char *) "ghi", NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list22 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list23 = list_item_new((char *) "ghi", NULL, NULL);
    ADTListItem list24 = list_item_new((char *) "jkl", NULL, NULL);
    list2->head = list21;
    list2->tail = list24;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_next(list23, list24);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    list_item_set_prev(list24, list23);
    g_assert_cmpint(list_equals_cmp(list1, list2, (int (*)(void *, void *)) str_equals), ==,
                    0);
    list_release(list1);
    list_release(list2);
}

static void test_list_to_str_1() {
    ADTList list = list_new();
    char *str = list_to_str(list, (char *(*)(void *)) str_dup);
    g_assert_cmpstr(str, ==, (char *) "");
    free(str);
    list_release(list);
}

static void test_list_to_str_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    char *str = list_to_str(list, (char *(*)(void *)) str_dup);
    g_assert_cmpstr(str, ==, (char *) "abc");
    free(str);
    list_release(list);
}

static void test_list_to_str_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    char *str = list_to_str(list, (char *(*)(void *)) str_dup);
    g_assert_cmpstr(str, ==, (char *) "abc,def,ghi");
    free(str);
    list_release(list);
}

static void test_list_to_str_4() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc,", NULL, NULL);
    list->head = list->tail = list1;
    char *str = list_to_str(list, (char *(*)(void *)) str_dup);
    g_assert_cmpstr(str, ==, (char *) "abc\\,");
    free(str);
    list_release(list);
}

static void test_list_to_str_5() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc,", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def,", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi,", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    char *str = list_to_str(list, (char *(*)(void *)) str_dup);
    g_assert_cmpstr(str, ==, (char *) "abc\\,,def\\,,ghi\\,");
    free(str);
    list_release(list);
}

static void test_list_from_str_1() {
    ADTList from_str = list_from_str((char *) "", (void *(*)(char *)) str_dup);
    ADTList list = list_new();
    g_assert_cmpint(list_equals_cmp(list, from_str, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(from_str);
}

static void test_list_from_str_2() {
    ADTList from_str = list_from_str((char *) "abc", (void *(*)(char *)) str_dup);
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    g_assert_cmpint(list_equals_cmp(list, from_str, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_full_release(from_str, free);
}

static void test_list_from_str_3() {
    ADTList from_str = list_from_str((char *) "abc,def,ghi", (void *(*)(char *)) str_dup);
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_equals_cmp(list, from_str, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_full_release(from_str, free);
}

static void test_list_from_str_4() {
    ADTList from_str = list_from_str((char *) "abc\\,", (void *(*)(char *)) str_dup);
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc,", NULL, NULL);
    list->head = list->tail = list1;
    g_assert_cmpint(list_equals_cmp(list, from_str, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_full_release(from_str, free);
}

static void test_list_from_str_5() {
    ADTList from_str = list_from_str((char *) "abc\\,,def\\,,ghi\\,", (void *(*)(char *)) str_dup);
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc,", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def,", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi,", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_equals_cmp(list, from_str, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_full_release(from_str, free);
}

static void test_list_dup_1() {
    ADTList list = list_new();
    ADTList dup = list_dup(list);
    g_assert_cmpint(list_equals(list, dup), ==, 1);
    list_release(list);
    list_release(dup);
}

static void test_list_dup_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    ADTList dup = list_dup(list);
    g_assert_cmpint(list_equals(list, dup), ==, 1);
    list_release(list);
    list_release(dup);
}

static void test_list_dup_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    ADTList dup = list_dup(list);
    g_assert_cmpint(list_equals(list, dup), ==, 1);
    list_release(list);
    list_release(dup);
}

static void test_list_get_head_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    g_assert(list_get_head(list) == list->head);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_get_head(list) == list->head);
    list_release(list);
}

static void test_list_set_head_1() {
    ADTList list = list_new();
    ADTListItem item = list_item_new(NULL, NULL, NULL);
    list_set_head(list, item);
    list->tail = item;
    g_assert(list->head == item);
    list_release(list);
}

static void test_list_get_tail_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    g_assert(list_get_tail(list) == list->tail);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_get_tail(list) == list->tail);
    list_release(list);
}

static void test_list_set_tail_1() {
    ADTList list = list_new();
    ADTListItem item = list_item_new(NULL, NULL, NULL);
    list->head = item;
    list_set_tail(list, item);
    g_assert(list->tail == item);
    list_release(list);
}

static void test_list_prev_1() {
    ADTListItem prev = list_item_new(NULL, NULL, NULL);
    ADTListItem item = list_item_new(NULL, prev, NULL);
    g_assert(list_prev(item) == item->prev);
    list_item_release(prev);
    list_item_release(item);
}

static void test_list_next_1() {
    ADTListItem next = list_item_new(NULL, NULL, NULL);
    ADTListItem item = list_item_new(NULL, NULL, next);
    g_assert(list_next(item) == item->next);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_value_1() {
    ADTListItem item = list_item_new((char *) "Sport Club Corinthians Paulista", NULL, NULL); 
    g_assert(list_value(item) == item->value);
    list_item_release(item);
}

static void test_list_head_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    g_assert(list_head(list) == list->head);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_head(list) == list->head);
    list_release(list);
}

static void test_list_tail_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    g_assert(list_tail(list) == list->tail);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_tail(list) == list->tail);
    list_release(list);
}

static void test_list_size_1() {
    ADTList list = list_new();
    g_assert_cmpint(list_size(list), ==, 0);
    list_release(list);
}

static void test_list_size_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_size(list), ==, 3);
    list_release(list);
}

static void test_list_item_at_1() {
    ADTList list = list_new();
    g_assert(list_item_at(list, 0) == NULL);
    g_assert(list_item_at(list, -1) == NULL);
    list_release(list);
}

static void test_list_item_at_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_item_at(list, 0) == list->head);
    g_assert(list_item_at(list, 1) == list->head->next);
    g_assert(list_item_at(list, 2) == list->head->next->next);
    g_assert(list_item_at(list, 3) == NULL);
    g_assert(list_item_at(list, -1) == list->tail);
    g_assert(list_item_at(list, -2) == list->tail->prev);
    g_assert(list_item_at(list, -3) == list->tail->prev->prev);
    g_assert(list_item_at(list, -4) == NULL);
    list_release(list);
}

static void test_list_at_1() {
    ADTList list = list_new();
    g_assert(list_at(list, 0) == NULL);
    g_assert(list_at(list, -1) == NULL);
    list_release(list);
}

static void test_list_at_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpstr((char *) list_at(list, 0), ==, (char *) "abc");
    g_assert_cmpstr((char *) list_at(list, 1), ==, (char *) "def");
    g_assert_cmpstr((char *) list_at(list, 2), ==, (char *) "ghi");
    g_assert(list_at(list, 3) == NULL);
    g_assert_cmpstr((char *) list_at(list, -1), ==, (char *) "ghi");
    g_assert_cmpstr((char *) list_at(list, -2), ==, (char *) "def");
    g_assert_cmpstr((char *) list_at(list, -3), ==, (char *) "abc");
    g_assert(list_at(list, -4) ==  NULL);
    list_release(list);
}

static void test_list_random_item_1() {
    ADTList list = list_new();
    g_assert(list_random_item(list) == NULL);
    list_release(list);
}

static void test_list_random_item_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    ADTListItem item = list_random_item(list);
    g_assert(item == list->head || item == list->head->next || item == list->tail);
    list_release(list);
}

static void test_list_random_1() {
    ADTList list = list_new();
    g_assert(list_random(list) == NULL);
    list_release(list);
}

static void test_list_random_2() {
    ADTList list = list_new();
    ADTListItem item = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = item;
    g_assert_cmpstr((char *) list_random(list), ==, (char *) "abc");
    list_release(list);
}

static void test_list_insert_before_item_1() {
    ADTList list = list_new();
    list_insert_before_item(list, (char *) "4", NULL);
    list_insert_before_item(list, (char *) "1", list->head);
    list_insert_before_item(list, (char *) "2", list->head->next);
    list_insert_before_item(list, (char *) "3", list->tail);
    list_insert_before_item(list, (char *) "5", NULL);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "1", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "2", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "3", NULL, NULL);
    ADTListItem result4 = list_item_new((char *) "4", NULL, NULL);
    ADTListItem result5 = list_item_new((char *) "5", NULL, NULL);
    result->head = result1;
    result->tail = result5;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_next(result3, result4);
    list_item_set_next(result4, result5);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    list_item_set_prev(result4, result3);
    list_item_set_prev(result5, result4);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_insert_after_item_1() {
    ADTList list = list_new();
    list_insert_after_item(list, (char *) "2", NULL);
    list_insert_after_item(list, (char *) "3", list->head);
    list_insert_after_item(list, (char *) "4", list->head->next);
    list_insert_after_item(list, (char *) "5", list->tail);
    list_insert_after_item(list, (char *) "1", NULL);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "1", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "2", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "3", NULL, NULL);
    ADTListItem result4 = list_item_new((char *) "4", NULL, NULL);
    ADTListItem result5 = list_item_new((char *) "5", NULL, NULL);
    result->head = result1;
    result->tail = result5;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_next(result3, result4);
    list_item_set_next(result4, result5);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    list_item_set_prev(result4, result3);
    list_item_set_prev(result5, result4);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_insert_1() {
    ADTList list = list_new();
    list_insert(list, (char *) "1", 0);
    list_insert(list, (char *) "2", 1);
    list_insert(list, (char *) "3", 2);
    list_insert(list, (char *) "4", 3);
    list_insert(list, (char *) "5", 4);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "1", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "2", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "3", NULL, NULL);
    ADTListItem result4 = list_item_new((char *) "4", NULL, NULL);
    ADTListItem result5 = list_item_new((char *) "5", NULL, NULL);
    result->head = result1;
    result->tail = result5;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_next(result3, result4);
    list_item_set_next(result4, result5);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    list_item_set_prev(result4, result3);
    list_item_set_prev(result5, result4);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_insert_2() {
    ADTList list = list_new();
    list_insert(list, (char *) "2", -10);
    list_insert(list, (char *) "3", -1);
    list_insert(list, (char *) "1", -3);
    list_insert(list, (char *) "4", 3);
    list_insert(list, (char *) "5", 10);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "1", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "2", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "3", NULL, NULL);
    ADTListItem result4 = list_item_new((char *) "4", NULL, NULL);
    ADTListItem result5 = list_item_new((char *) "5", NULL, NULL);
    result->head = result1;
    result->tail = result5;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_next(result3, result4);
    list_item_set_next(result4, result5);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    list_item_set_prev(result4, result3);
    list_item_set_prev(result5, result4);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_prepend_1() {
    ADTList list = list_new();
    list_prepend(list, (char *) "ghi");
    list_prepend(list, (char *) "def");
    list_prepend(list, (char *) "abc");
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "ghi", NULL, NULL);
    result->head = result1;
    result->tail = result3;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_append_1() {
    ADTList list = list_new();
    list_append(list, (char *) "abc");
    list_append(list, (char *) "def");
    list_append(list, (char *) "ghi");
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "ghi", NULL, NULL);
    result->head = result1;
    result->tail = result3;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_remove_item_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_remove_item(list, list->head);
    list_remove_item(list, list->tail);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_remove_full_item_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "def"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) "ghi"), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_remove_full_item(list, list->head, free);
    list_remove_full_item(list, list->tail, free);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(list, free);
    list_release(result);
}

static void test_list_remove_at_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_remove_at(list, 0);
    list_remove_at(list, -1);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_full_remove_at_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "def"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) "ghi"), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_remove_at(list, 0, free);
    list_full_remove_at(list, -1, free);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(list, free);
    list_release(result);
}

static void test_list_remove_1() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(value1, NULL, NULL);
    ADTListItem list2 = list_item_new(value2, NULL, NULL);
    ADTListItem list3 = list_item_new(value3, NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_remove(list, value1);
    list_remove(list, value2);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new(value3, NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_full_remove_1() {
    char *value1 = str_dup((char *) "abc");
    char *value2 = str_dup((char *) "def");
    char *value3 = str_dup((char *) "ghi");
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(value1, NULL, NULL);
    ADTListItem list2 = list_item_new(value2, NULL, NULL);
    ADTListItem list3 = list_item_new(value3, NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_remove(list, value1, free);
    list_full_remove(list, value2, free);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new(value3, NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(list, free);
    list_release(result);
}

static void test_list_remove_cmp_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_remove_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "abc");
    list_remove_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "ghi");
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_full_remove_cmp_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "def"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) "ghi"), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_remove_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "abc", free);
    list_full_remove_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "ghi", free);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(list, free);
    list_release(result);
}

static void test_list_pop_front_1() {
    ADTList list = list_new();
    g_assert(list_pop_front(list) == NULL);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_pop_front_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpstr((char *) list_pop_front(list), ==, (char *) "abc");
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "ghi", NULL, NULL);
    result->head = result1;
    result->tail = result2;
    list_item_set_next(result1, result2);
    list_item_set_prev(result2, result1);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_pop_back_1() {
    ADTList list = list_new();
    g_assert(list_pop_back(list) == NULL);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_pop_back_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpstr((char *) list_pop_back(list), ==, (char *) "ghi");
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "def", NULL, NULL);
    result->head = result1;
    result->tail = result2;
    list_item_set_next(result1, result2);
    list_item_set_prev(result2, result1);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_pop_random_1() {
    ADTList list = list_new();
    g_assert(list_pop_random(list) == NULL);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_pop_random_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    g_assert_cmpstr((char *) list_pop_random(list), ==, (char *) "abc");
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_clear_1() {
    ADTList list = list_new();
    list_clear(list);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_clear_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_clear(list);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_full_clear_1() {
    ADTList list = list_new();
    list_full_clear(list, free);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_full_clear_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "def"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) "ghi"), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_clear(list, free);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_extend_1() {
    ADTList list1 = list_new();
    ADTList list2 = list_new();
    list_extend(list1, list2);
    ADTList result = list_new();
    g_assert_cmpint(list_equals_cmp(list1, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(result);
}

static void test_list_extend_2() {
    ADTList list1 = list_new();
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "abc", NULL, NULL);
    list2->head = list2->tail = list21;
    list_extend(list1, list2);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list1, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(result);
}

static void test_list_extend_3() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    list1->head = list1->tail = list11;
    ADTList list2 = list_new();
    list_extend(list1, list2);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list1, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(result);
}

static void test_list_extend_4() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    list1->head = list1->tail = list11;
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list22 = list_item_new((char *) "ghi", NULL, NULL);
    list_item_set_next(list21, list22);
    list_item_set_prev(list22, list21);
    list2->head = list21;
    list2->tail = list22;
    list_extend(list1, list2);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "ghi", NULL, NULL);
    result->head = result1;
    result->tail = result3;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    g_assert_cmpint(list_equals_cmp(list1, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(result);
}

static void test_list_map_1() {
    ADTList list = list_new();
    ADTList map = list_map(list, (void *(*)(void *)) str_reverse);
    g_assert_cmpint(list_equals(list, map), ==, 1);
    list_release(list);
    list_release(map);
}

static void test_list_map_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    ADTList map = list_map(list, (void *(*)(void *)) str_reverse);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "cba", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(map, result, (int (*)(void *, void *)) str_equals), ==, 1);
    list_release(list);
    list_release(result);
    list_full_release(map, free);
}

static void test_list_map_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    ADTList map = list_map(list, (void *(*)(void *)) str_reverse);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "cba", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "fed", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "ihg", NULL, NULL);
    result->head = result1;
    result->tail = result3;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    g_assert_cmpint(list_equals_cmp(map, result, (int (*)(void *, void *)) str_equals), ==, 1);
    list_release(list);
    list_release(result);
    list_full_release(map, free);
}

static void test_list_find_1() {
    ADTList list = list_new();
    g_assert(list_find(list, (char *) "abc") == NULL);
    list_release(list);
}

static void test_list_find_2() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    char *value4 = (char *) "jkl";
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(value1, NULL, NULL);
    ADTListItem list2 = list_item_new(value2, NULL, NULL);
    ADTListItem list3 = list_item_new(value3, NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_find(list, value4) == NULL);
    list_release(list);
}

static void test_list_find_3() {
    char *value1 = (char *) "abc";
    char *value2 = (char *) "def";
    char *value3 = (char *) "ghi";
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(value1, NULL, NULL);
    ADTListItem list2 = list_item_new(value2, NULL, NULL);
    ADTListItem list3 = list_item_new(value3, NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_find(list, value1) == list1);
    list_release(list);
}

static void test_list_find_cmp_1() {
    ADTList list = list_new();
    g_assert(list_find_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "abc") ==
             NULL);
    list_release(list);
}

static void test_list_find_cmp_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_find_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "jkl") ==
             NULL);
    list_release(list);
}

static void test_list_find_cmp_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert(list_find_cmp(list, (int (*)(void *, void *)) str_equals, (char *) "abc") ==
             list1);
    list_release(list);
}

static void test_list_index_1() {
    ADTList list = list_new();
    g_assert_cmpint(list_index(list, list->head), ==, -1);
    g_assert_cmpint(list_index(list, list->tail), ==, -1);
    list_release(list);
}

static void test_list_index_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    g_assert_cmpint(list_index(list, list->head), ==, 0);
    g_assert_cmpint(list_index(list, list->tail), ==, 0);
    list_release(list);
}

static void test_list_index_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_index(list, list->head), ==, 0);
    g_assert_cmpint(list_index(list, list->head->next), ==, 1);
    g_assert_cmpint(list_index(list, list->tail), ==, 2);
    list_release(list);
}

static void test_list_min_1() {
    ADTList list = list_new();
    g_assert_cmpint(list_min(list, (int (*)(void *)) strlen), ==, INT_MAX);
    list_release(list);
}

static void test_list_min_2() {
    ADTList list = list_new();
    ADTListItem item = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = item;
    g_assert_cmpint(list_min(list, (int (*)(void *)) strlen), ==, 3);
    list_release(list);
}

static void test_list_min_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "a", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "ab", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_min(list, (int (*)(void *)) strlen), ==, 1);
    list_release(list);
}

static void test_list_max_1() {
    ADTList list = list_new();
    g_assert_cmpint(list_max(list, (int (*)(void *)) strlen), ==, INT_MIN);
    list_release(list);
}

static void test_list_max_2() {
    ADTList list = list_new();
    ADTListItem item = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = item;
    g_assert_cmpint(list_max(list, (int (*)(void *)) strlen), ==, 3);
    list_release(list);
}

static void test_list_max_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "a", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "ab", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    g_assert_cmpint(list_max(list, (int (*)(void *)) strlen), ==, 3);
    list_release(list);
}

static void test_list_reverse_1() {
    ADTList list = list_new();
    list_reverse(list);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_reverse_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    list->head = list->tail = list1;
    list_reverse(list);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_reverse_3() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "ghi", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_reverse(list);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "ghi", NULL, NULL);
    ADTListItem result2 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem result3 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result1;
    result->tail = result3;
    list_item_set_next(result1, result2);
    list_item_set_next(result2, result3);
    list_item_set_prev(result2, result1);
    list_item_set_prev(result3, result2);
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_foreach_1() {
    ADTList list = list_new();
    list_foreach(list, (void (*)(void *)) list_reverse);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_foreach_2() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    list1->head = list1->tail = list11;
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "abc", NULL, NULL);
    list2->head = list2->tail = list21;
    ADTList list3 = list_new();
    ADTListItem list31 = list_item_new(list1, NULL, NULL);
    ADTListItem list32 = list_item_new(list2, NULL, NULL);
    list3->head = list31;
    list3->tail = list32;
    list_item_set_next(list31, list32);
    list_item_set_prev(list32, list31);
    list_foreach(list3, (void (*)(void *)) list_reverse);
    ADTList list4 = list_new();
    ADTListItem list41 = list_item_new((char *) "abc", NULL, NULL);
    list4->head = list4->tail = list41;
    ADTList list5 = list_new();
    ADTListItem list51 = list_item_new((char *) "abc", NULL, NULL);
    list5->head = list5->tail = list51;
    g_assert_cmpint(list_equals_cmp(list1, list5, (int (*)(void *, void *)) str_equals), ==,
                    1);
    g_assert_cmpint(list_equals_cmp(list2, list4, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(list3);
    list_release(list4);
    list_release(list5);
}

static void test_list_foreach_3() {
    ADTList list1 = list_new();
    ADTListItem list11 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list12 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list13 = list_item_new((char *) "ghi", NULL, NULL);
    list1->head = list11;
    list1->tail = list13;
    list_item_set_next(list11, list12);
    list_item_set_next(list12, list13);
    list_item_set_prev(list12, list11);
    list_item_set_prev(list13, list12);
    ADTList list2 = list_new();
    ADTListItem list21 = list_item_new((char *) "ghi", NULL, NULL);
    ADTListItem list22 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list23 = list_item_new((char *) "abc", NULL, NULL);
    list2->head = list21;
    list2->tail = list23;
    list_item_set_next(list21, list22);
    list_item_set_next(list22, list23);
    list_item_set_prev(list22, list21);
    list_item_set_prev(list23, list22);
    ADTList list3 = list_new();
    ADTListItem list31 = list_item_new(list1, NULL, NULL);
    ADTListItem list32 = list_item_new(list2, NULL, NULL);
    list3->head = list31;
    list3->tail = list32;
    list_item_set_next(list31, list32);
    list_item_set_prev(list32, list31);
    list_foreach(list3, (void (*)(void *)) list_reverse);
    ADTList list4 = list_new();
    ADTListItem list41 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list42 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list43 = list_item_new((char *) "ghi", NULL, NULL);
    list4->head = list41;
    list4->tail = list43;
    list_item_set_next(list41, list42);
    list_item_set_next(list42, list43);
    list_item_set_prev(list42, list41);
    list_item_set_prev(list43, list42);
    ADTList list5 = list_new();
    ADTListItem list51 = list_item_new((char *) "ghi", NULL, NULL);
    ADTListItem list52 = list_item_new((char *) "def", NULL, NULL);
    ADTListItem list53 = list_item_new((char *) "abc", NULL, NULL);
    list5->head = list51;
    list5->tail = list53;
    list_item_set_next(list51, list52);
    list_item_set_next(list52, list53);
    list_item_set_prev(list52, list51);
    list_item_set_prev(list53, list52);
    g_assert_cmpint(list_equals_cmp(list1, list5, (int (*)(void *, void *)) str_equals), ==,
                    1);
    g_assert_cmpint(list_equals_cmp(list2, list4, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list1);
    list_release(list2);
    list_release(list3);
    list_release(list4);
    list_release(list5);
}

static void test_list_filter_1() {
    ADTList list = list_new();
    list_filter(list, (int (*)(void *)) strlen);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_filter_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new((char *) "", NULL, NULL);
    ADTListItem list2 = list_item_new((char *) "abc", NULL, NULL);
    ADTListItem list3 = list_item_new((char *) "", NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_filter(list, (int (*)(void *)) strlen);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(list);
    list_release(result);
}

static void test_list_full_filter_1() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) ""), NULL, NULL);
    list->head = list->tail = list1;
    list_full_filter(list, (int (*)(void *)) strlen, free);
    g_assert(list->head == NULL && list->tail == NULL);
    list_release(list);
}

static void test_list_full_filter_2() {
    ADTList list = list_new();
    ADTListItem list1 = list_item_new(str_dup((char *) ""), NULL, NULL);
    ADTListItem list2 = list_item_new(str_dup((char *) "abc"), NULL, NULL);
    ADTListItem list3 = list_item_new(str_dup((char *) ""), NULL, NULL);
    list->head = list1;
    list->tail = list3;
    list_item_set_next(list1, list2);
    list_item_set_next(list2, list3);
    list_item_set_prev(list2, list1);
    list_item_set_prev(list3, list2);
    list_full_filter(list, (int (*)(void *)) strlen, free);
    ADTList result = list_new();
    ADTListItem result1 = list_item_new((char *) "abc", NULL, NULL);
    result->head = result->tail = result1;
    g_assert_cmpint(list_equals_cmp(list, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(list, free);
    list_release(result);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/list/new", test_list_new_1);
    g_test_add_func("/list/release", test_list_release_1);
    g_test_add_func("/list/release", test_list_release_2);
    g_test_add_func("/list/full_release", test_list_full_release_1);
    g_test_add_func("/list/full_release", test_list_full_release_2);
    g_test_add_func("/list/equals", test_list_equals_1);
    g_test_add_func("/list/equals", test_list_equals_2);
    g_test_add_func("/list/equals", test_list_equals_3);
    g_test_add_func("/list/equals", test_list_equals_4);
    g_test_add_func("/list/equals_cmp", test_list_equals_cmp_1);
    g_test_add_func("/list/equals_cmp", test_list_equals_cmp_2);
    g_test_add_func("/list/equals_cmp", test_list_equals_cmp_3);
    g_test_add_func("/list/equals_cmp", test_list_equals_cmp_4);
    g_test_add_func("/list/to_str", test_list_to_str_1);
    g_test_add_func("/list/to_str", test_list_to_str_2);
    g_test_add_func("/list/to_str", test_list_to_str_3);
    g_test_add_func("/list/to_str", test_list_to_str_4);
    g_test_add_func("/list/to_str", test_list_to_str_5);
    g_test_add_func("/list/from_str", test_list_from_str_1);
    g_test_add_func("/list/from_str", test_list_from_str_2);
    g_test_add_func("/list/from_str", test_list_from_str_3);
    g_test_add_func("/list/from_str", test_list_from_str_4);
    g_test_add_func("/list/from_str", test_list_from_str_5);
    g_test_add_func("/list/dup", test_list_dup_1);
    g_test_add_func("/list/dup", test_list_dup_2);
    g_test_add_func("/list/dup", test_list_dup_3);
    g_test_add_func("/list/get_head", test_list_get_head_1);
    g_test_add_func("/list/set_head", test_list_set_head_1);
    g_test_add_func("/list/get_tail", test_list_get_tail_1);
    g_test_add_func("/list/set_tail", test_list_set_tail_1);
    g_test_add_func("/list/prev", test_list_prev_1);
    g_test_add_func("/list/next", test_list_next_1);
    g_test_add_func("/list/value", test_list_value_1);
    g_test_add_func("/list/head", test_list_head_1);
    g_test_add_func("/list/tail", test_list_tail_1);
    g_test_add_func("/list/size", test_list_size_1);
    g_test_add_func("/list/size", test_list_size_2);
    g_test_add_func("/list/item_at", test_list_item_at_1);
    g_test_add_func("/list/item_at", test_list_item_at_2);
    g_test_add_func("/list/at", test_list_at_1);
    g_test_add_func("/list/at", test_list_at_2);
    g_test_add_func("/list/random_item", test_list_random_item_1);
    g_test_add_func("/list/random_item", test_list_random_item_2);
    g_test_add_func("/list/random", test_list_random_1);
    g_test_add_func("/list/random", test_list_random_2);
    g_test_add_func("/list/insert_before_item", test_list_insert_before_item_1);
    g_test_add_func("/list/insert_after_item", test_list_insert_after_item_1);
    g_test_add_func("/list/insert", test_list_insert_1);
    g_test_add_func("/list/insert", test_list_insert_2);
    g_test_add_func("/list/prepend", test_list_prepend_1);
    g_test_add_func("/list/append", test_list_append_1);
    g_test_add_func("/list/remove_item", test_list_remove_item_1);
    g_test_add_func("/list/remove_full_item", test_list_remove_full_item_1);
    g_test_add_func("/list/remove_at", test_list_remove_at_1);
    g_test_add_func("/list/full_remove_at", test_list_full_remove_at_1);
    g_test_add_func("/list/remove", test_list_remove_1);
    g_test_add_func("/list/full_remove", test_list_full_remove_1);
    g_test_add_func("/list/remove_cmp", test_list_remove_cmp_1);
    g_test_add_func("/list/full_remove_cmp", test_list_full_remove_cmp_1);
    g_test_add_func("/list/pop_front", test_list_pop_front_1);
    g_test_add_func("/list/pop_front", test_list_pop_front_2);
    g_test_add_func("/list/pop_back", test_list_pop_back_1);
    g_test_add_func("/list/pop_back", test_list_pop_back_2);
    g_test_add_func("/list/pop_random", test_list_pop_random_1);
    g_test_add_func("/list/pop_random", test_list_pop_random_2);
    g_test_add_func("/list/clear", test_list_clear_1);
    g_test_add_func("/list/clear", test_list_clear_2);
    g_test_add_func("/list/full_clear", test_list_full_clear_1);
    g_test_add_func("/list/full_clear", test_list_full_clear_2);
    g_test_add_func("/list/extend", test_list_extend_1);
    g_test_add_func("/list/extend", test_list_extend_2);
    g_test_add_func("/list/extend", test_list_extend_3);
    g_test_add_func("/list/extend", test_list_extend_4);
    g_test_add_func("/list/map", test_list_map_1);
    g_test_add_func("/list/map", test_list_map_2);
    g_test_add_func("/list/map", test_list_map_3);
    g_test_add_func("/list/find", test_list_find_1);
    g_test_add_func("/list/find", test_list_find_2);
    g_test_add_func("/list/find", test_list_find_3);
    g_test_add_func("/list/find_cmp", test_list_find_cmp_1);
    g_test_add_func("/list/find_cmp", test_list_find_cmp_2);
    g_test_add_func("/list/find_cmp", test_list_find_cmp_3);
    g_test_add_func("/list/index", test_list_index_1);
    g_test_add_func("/list/index", test_list_index_2);
    g_test_add_func("/list/index", test_list_index_3);
    g_test_add_func("/list/min", test_list_min_1);
    g_test_add_func("/list/min", test_list_min_2);
    g_test_add_func("/list/min", test_list_min_3);
    g_test_add_func("/list/max", test_list_max_1);
    g_test_add_func("/list/max", test_list_max_2);
    g_test_add_func("/list/max", test_list_max_3);
    g_test_add_func("/list/reverse", test_list_reverse_1);
    g_test_add_func("/list/reverse", test_list_reverse_2);
    g_test_add_func("/list/reverse", test_list_reverse_3);
    g_test_add_func("/list/foreach", test_list_foreach_1);
    g_test_add_func("/list/foreach", test_list_foreach_2);
    g_test_add_func("/list/foreach", test_list_foreach_3);
    g_test_add_func("/list/filter", test_list_filter_1);
    g_test_add_func("/list/filter", test_list_filter_2);
    g_test_add_func("/list/full_filter", test_list_full_filter_1);
    g_test_add_func("/list/full_filter", test_list_full_filter_2);
    return g_test_run();
}

