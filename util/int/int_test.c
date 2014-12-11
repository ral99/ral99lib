#include <glib.h>
#include <stdlib.h>

#include "util/int/int.h"

static void test_int_to_pointer_1() {
    int value = -2147483647;
    g_assert(int_to_pointer(value) == (void *) ((long) value));
}

static void test_int_to_pointer_2() {
    int value = -1;
    g_assert(int_to_pointer(value) == (void *) ((long) value));
}

static void test_int_to_pointer_3() {
    int value = 0;
    g_assert(int_to_pointer(value) == (void *) ((long) value));
}

static void test_int_to_pointer_4() {
    int value = 1;
    g_assert(int_to_pointer(value) == (void *) ((long) value));
}

static void test_int_to_pointer_5() {
    int value = 2147483647;
    g_assert(int_to_pointer(value) == (void *) ((long) value));
}

static void test_int_from_pointer_1() {
    int value = -2147483647;
    g_assert_cmpint(int_from_pointer((void *) ((long) value)), ==, value);
}

static void test_int_from_pointer_2() {
    int value = -1;
    g_assert_cmpint(int_from_pointer((void *) ((long) value)), ==, value);
}

static void test_int_from_pointer_3() {
    int value = 0;
    g_assert_cmpint(int_from_pointer((void *) ((long) value)), ==, value);
}

static void test_int_from_pointer_4() {
    int value = 1;
    g_assert_cmpint(int_from_pointer((void *) ((long) value)), ==, value);
}

static void test_int_from_pointer_5() {
    int value = 2147483647;
    g_assert_cmpint(int_from_pointer((void *) ((long) value)), ==, value);
}

static void test_int_random_1() {
    int start = 0;
    int end = 0;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_random_2() {
    int start = -10;
    int end = -10;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_random_3() {
    int start = 10;
    int end = 10;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_random_4() {
    int start = -10;
    int end = -1;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_random_5() {
    int start = 1;
    int end = 10;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_random_6() {
    int start = -10;
    int end = 10;
    int x = int_random(start, end);
    g_assert(x >= start && x <= end);
}

static void test_int_to_str_1() {
    char *str = int_to_str(0);
    g_assert_cmpstr(str, ==, "0");
    free(str);
}

static void test_int_to_str_2() {
    char *str = int_to_str(1234567890);
    g_assert_cmpstr(str, ==, "1234567890");
    free(str);
}

static void test_int_to_str_3() {
    char *str = int_to_str(-1234567890);
    g_assert_cmpstr(str, ==, "-1234567890");
    free(str);
}

static void test_int_from_str_1() {
    g_assert_cmpint(int_from_str("0"), ==, 0);
}

static void test_int_from_str_2() {
    g_assert_cmpint(int_from_str("1234567890"), ==, 1234567890);
}

static void test_int_from_str_3() {
    g_assert_cmpint(int_from_str("-1234567890"), ==, -1234567890);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/int/to_pointer", test_int_to_pointer_1);
    g_test_add_func("/int/to_pointer", test_int_to_pointer_2);
    g_test_add_func("/int/to_pointer", test_int_to_pointer_3);
    g_test_add_func("/int/to_pointer", test_int_to_pointer_4);
    g_test_add_func("/int/to_pointer", test_int_to_pointer_5);
    g_test_add_func("/int/from_pointer", test_int_from_pointer_1);
    g_test_add_func("/int/from_pointer", test_int_from_pointer_2);
    g_test_add_func("/int/from_pointer", test_int_from_pointer_3);
    g_test_add_func("/int/from_pointer", test_int_from_pointer_4);
    g_test_add_func("/int/from_pointer", test_int_from_pointer_5);
    g_test_add_func("/int/random", test_int_random_1);
    g_test_add_func("/int/random", test_int_random_2);
    g_test_add_func("/int/random", test_int_random_3);
    g_test_add_func("/int/random", test_int_random_4);
    g_test_add_func("/int/random", test_int_random_5);
    g_test_add_func("/int/random", test_int_random_6);
    g_test_add_func("/int/to_str", test_int_to_str_1);
    g_test_add_func("/int/to_str", test_int_to_str_2);
    g_test_add_func("/int/to_str", test_int_to_str_3);
    g_test_add_func("/int/from_str", test_int_from_str_1);
    g_test_add_func("/int/from_str", test_int_from_str_2);
    g_test_add_func("/int/from_str", test_int_from_str_3);
    return g_test_run();
}

