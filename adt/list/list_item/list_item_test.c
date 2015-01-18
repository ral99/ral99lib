#include <glib.h>
#include <stdlib.h>

#include "adt/adt.h"
#include "str/str.h"

static void test_list_item_new_1() {
    char *value = "Sport Club Corinthians Paulista";
    ListItem prev = list_item_new(NULL, NULL, NULL);
    ListItem next = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(value, prev, next);
    g_assert(item->value == value);
    g_assert(item->prev == prev);
    g_assert(item->next == next);
    list_item_release(prev);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_item_release_1() {
    ListItem item = list_item_new(NULL, NULL, NULL);
    list_item_release(item);
}

static void test_list_item_full_release_1() {
    ListItem item = list_item_new(str_dup("Corinthians"), NULL, NULL);
    list_item_full_release(item, free);
}

static void test_list_item_get_prev_1() {
    ListItem prev = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, prev, NULL);
    g_assert(list_item_get_prev(item) == item->prev);
    list_item_release(prev);
    list_item_release(item);
}

static void test_list_item_set_prev_1() {
    ListItem item = list_item_new(NULL, NULL, NULL);
    ListItem prev = list_item_new(NULL, NULL, NULL);
    list_item_set_prev(item, prev);
    g_assert(item->prev == prev);
    list_item_release(prev);
    list_item_release(item);
}

static void test_list_item_get_next_1() {
    ListItem next = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, NULL, next);
    g_assert(list_item_get_next(item) == item->next);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_item_set_next_1() {
    ListItem item = list_item_new(NULL, NULL, NULL);
    ListItem next = list_item_new(NULL, NULL, NULL);
    list_item_set_next(item, next);
    g_assert(item->next == next);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_item_get_value_1() {
    ListItem item = list_item_new("Sport Club Corinthians Paulista", NULL, NULL);
    g_assert(list_item_get_value(item) == item->value);
    list_item_release(item);
}

static void test_list_item_set_value_1() {
    ListItem item = list_item_new(NULL, NULL, NULL);
    char *value = "Sport Club Corinthians Paulista";
    list_item_set_value(item, value);
    g_assert(item->value == value);
    list_item_release(item);
}

static void test_list_item_prev_is_1() {
    ListItem prev = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, prev, NULL);
    g_assert_cmpint(list_item_prev_is(item, prev), ==, 1);
    list_item_release(prev);
    list_item_release(item);
}

static void test_list_item_prev_is_2() {
    ListItem a = list_item_new(NULL, NULL, NULL);
    ListItem b = list_item_new(NULL, NULL, NULL);
    g_assert_cmpint(list_item_prev_is(a, b), ==, 0);
    list_item_release(b);
    list_item_release(a);
}

static void test_list_item_next_is_1() {
    ListItem next = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, NULL, next);
    g_assert_cmpint(list_item_next_is(item, next), ==, 1);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_item_next_is_2() {
    ListItem a = list_item_new(NULL, NULL, NULL);
    ListItem b = list_item_new(NULL, NULL, NULL);
    g_assert_cmpint(list_item_next_is(a, b), ==, 0);
    list_item_release(b);
    list_item_release(a);
}

static void test_list_item_value_is_1() {
    char *value = "Sport Club Corinthians Paulista";
    ListItem item = list_item_new(value, NULL, NULL);
    g_assert_cmpint(list_item_value_is(item, value), ==, 1);
    list_item_release(item);
}

static void test_list_item_value_is_2() {
    char *value1 = "Sport Club Corinthians Paulista";
    char *value2 = "Republica Federativa do Brasil";
    ListItem item = list_item_new(value1, NULL, NULL);
    g_assert_cmpint(list_item_value_is(item, value2), ==, 0);
    list_item_release(item);
}

static void test_list_item_prev_1() {
    ListItem prev = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, prev, NULL);
    g_assert(list_item_prev(item) == item->prev);
    list_item_release(prev);
    list_item_release(item);
}

static void test_list_item_next_1() {
    ListItem next = list_item_new(NULL, NULL, NULL);
    ListItem item = list_item_new(NULL, NULL, next);
    g_assert(list_item_next(item) == item->next);
    list_item_release(next);
    list_item_release(item);
}

static void test_list_item_value_1() {
    ListItem item = list_item_new("Sport Club Corinthians Paulista", NULL, NULL);
    g_assert(list_item_value(item) == item->value);
    list_item_release(item);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/list_item/new", test_list_item_new_1);
    g_test_add_func("/list_item/release", test_list_item_release_1);
    g_test_add_func("/list_item/full_release", test_list_item_full_release_1);
    g_test_add_func("/list_item/get_prev", test_list_item_get_prev_1);
    g_test_add_func("/list_item/set_prev", test_list_item_set_prev_1);
    g_test_add_func("/list_item/get_next", test_list_item_get_next_1);
    g_test_add_func("/list_item/set_next", test_list_item_set_next_1);
    g_test_add_func("/list_item/get_value", test_list_item_get_value_1);
    g_test_add_func("/list_item/set_value", test_list_item_set_value_1);
    g_test_add_func("/list_item/prev_is", test_list_item_prev_is_1);
    g_test_add_func("/list_item/prev_is", test_list_item_prev_is_2);
    g_test_add_func("/list_item/next_is", test_list_item_next_is_1);
    g_test_add_func("/list_item/next_is", test_list_item_next_is_2);
    g_test_add_func("/list_item/value_is", test_list_item_value_is_1);
    g_test_add_func("/list_item/value_is", test_list_item_value_is_2);
    g_test_add_func("/list_item/prev", test_list_item_prev_1);
    g_test_add_func("/list_item/next", test_list_item_next_1);
    g_test_add_func("/list_item/value", test_list_item_value_1);
    return g_test_run();
}

