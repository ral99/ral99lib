#include <glib.h>
#include <stdlib.h>

#include "num/num.h"

static void test_double_gt_1() {
    double a = 1.0000001;
    double b = 1.0000000;
    
    g_assert_cmpint(double_gt(a, a), ==, 0);
    g_assert_cmpint(double_gt(b, b), ==, 0);
    g_assert_cmpint(double_gt(a, b), ==, 1);
    g_assert_cmpint(double_gt(b, a), ==, 0);
}

static void test_double_lt_1() {
    double a = 1.0000001;
    double b = 1.0000000;
    
    g_assert_cmpint(double_lt(a, a), ==, 0);
    g_assert_cmpint(double_lt(b, b), ==, 0);
    g_assert_cmpint(double_lt(a, b), ==, 0);
    g_assert_cmpint(double_lt(b, a), ==, 1);
}

static void test_double_equals_1() {
    double a = 1.0000001;
    double b = 1.0000000;
    
    g_assert_cmpint(double_equals(a, a), ==, 1);
    g_assert_cmpint(double_equals(b, b), ==, 1);
    g_assert_cmpint(double_equals(a, b), ==, 0);
    g_assert_cmpint(double_equals(b, a), ==, 0);
}

static void test_double_to_str_1() {
    char *str = double_to_str(0, 1);
    g_assert_cmpstr(str, ==, "0.0");
    free(str);
}

static void test_double_to_str_2() {
    char *str = double_to_str(1.001, 3);
    g_assert_cmpstr(str, ==, "1.001");
    free(str);
}

static void test_double_from_str_1() {
    double x = double_from_str("0.0");
    g_assert_cmpint(double_equals(x, 0), ==, 1);
}

static void test_double_from_str_2() {
    double x = double_from_str("1.001");
    g_assert_cmpint(double_equals(x, 1.001), ==, 1);
}

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

static void test_int_gcd_1() {
    g_assert_cmpint(int_gcd(5, 0), ==, 5);
    g_assert_cmpint(int_gcd(5, 5), ==, 5);
    g_assert_cmpint(int_gcd(10, 15), ==, 5);
    g_assert_cmpint(int_gcd(3, 5), ==, 1);
}

static void test_uint64_lcm_1() {
    g_assert(uint64_lcm(5, 0) == (uint64_t) 5);
    g_assert(uint64_lcm(5, 5) == (uint64_t) 5);
    g_assert(uint64_lcm(10, 15) == (uint64_t) 30);
    g_assert(uint64_lcm(3, 5) == (uint64_t) 15);
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
    g_test_add_func("/double/gt", test_double_gt_1);
    g_test_add_func("/double/lt", test_double_lt_1);
    g_test_add_func("/double/equals", test_double_equals_1);
    g_test_add_func("/double/to_str", test_double_to_str_1);
    g_test_add_func("/double/to_str", test_double_to_str_2);
    g_test_add_func("/double/from_str", test_double_from_str_1);
    g_test_add_func("/double/from_str", test_double_from_str_2);
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
    g_test_add_func("/int/gcd", test_int_gcd_1);
    g_test_add_func("/uint64/lcm", test_uint64_lcm_1);
    g_test_add_func("/int/to_str", test_int_to_str_1);
    g_test_add_func("/int/to_str", test_int_to_str_2);
    g_test_add_func("/int/to_str", test_int_to_str_3);
    g_test_add_func("/int/from_str", test_int_from_str_1);
    g_test_add_func("/int/from_str", test_int_from_str_2);
    g_test_add_func("/int/from_str", test_int_from_str_3);
    return g_test_run();
}

