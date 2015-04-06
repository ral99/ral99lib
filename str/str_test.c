#include <glib.h>
#include <stdlib.h>
#include <string.h>

#include "str/str.h"
#include "adt/adt.h"

static void test_str_equals_1() {
    g_assert_cmpint(str_equals((char *) "", (char *) ""), ==, 1);
}

static void test_str_equals_2() {
    g_assert_cmpint(str_equals((char *) "Sport Club Corinthians Paulista",
                               (char *) "Sport Club Corinthians Paulista"), ==, 1);
}

static void test_str_equals_3() {
    g_assert_cmpint(str_equals((char *) "Sport Club Corinthians Paulista",
                               (char *) "Republica Oriental del Uruguay"), ==, 0);
}

static void test_str_dup_1() {
    char *dup = str_dup((char *) "");
    g_assert_cmpstr(dup, ==, "");
    free(dup);
}

static void test_str_dup_2() {
    char *dup = str_dup((char *) "Sport Club Corinthians Paulista");
    g_assert_cmpstr(dup, ==, (char *) "Sport Club Corinthians Paulista");
    free(dup);
}

static void test_str_random_1() {
    char *str = str_random(0);
    g_assert_cmpstr(str, ==, "");
    free(str);
}

static void test_str_random_2() {
    int len = 32;
    char *str = str_random(len);
    g_assert_cmpint((int) strlen(str), ==, len);
    for (int i = 0; i < len; i++)
        g_assert((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] >= 'A' && str[i] <= 'Z'));
    free(str);
}

static void test_str_substr_1() {
    char *substr = str_substr((char *) "", 0, 0);
    g_assert_cmpstr(substr, ==, "");
    free(substr);
}

static void test_str_substr_2() {
    char *substr = str_substr((char *) "Sport Club Corinthians Paulista", 0, 5);
    g_assert_cmpstr(substr, ==, "Sport");
    free(substr);
}

static void test_str_substr_3() {
    char *substr = str_substr((char *) "Sport Club Corinthians Paulista", 11, 11);
    g_assert_cmpstr(substr, ==, "Corinthians");
    free(substr);
}

static void test_str_cat_1() {
    char *cat = str_cat((char *) "", (char *) "");
    g_assert_cmpstr(cat, ==, "");
    free(cat);
}

static void test_str_cat_2() {
    char *cat = str_cat((char *) "Sport Club ", (char *) "Corinthians Paulista");
    g_assert_cmpstr(cat, ==, (char *) "Sport Club Corinthians Paulista");
    free(cat);
}

static void test_str_reverse_1() {
    char *reversed = str_reverse((char *) "");
    g_assert_cmpstr(reversed, ==, "");
    free(reversed);
}

static void test_str_reverse_2() {
    char *reversed = str_reverse((char *) "12345");
    g_assert_cmpstr(reversed, ==, "54321");
    free(reversed);
}

static void test_str_escape_1() {
    char *escaped = str_escape((char *) "", (char *) "");
    g_assert_cmpstr(escaped, ==, "");
    free(escaped);
}

static void test_str_escape_2() {
    char *escaped = str_escape((char *) "Sport Club Corinthians Paulista", (char *) "");
    g_assert_cmpstr(escaped, ==, (char *) "Sport Club Corinthians Paulista");
    free(escaped);
}

static void test_str_escape_3() {
    char *escaped = str_escape((char *) "\\Sport Clu\\b Corinthians Pau\\lista", (char *) "");
    g_assert_cmpstr(escaped, ==, "\\\\Sport Clu\\\\b Corinthians Pau\\\\lista");
    free(escaped);
}

static void test_str_escape_4() {
    char *escaped = str_escape((char *) "A", (char *) "A");
    g_assert_cmpstr(escaped, ==, "\\A");
    free(escaped);
}

static void test_str_escape_5() {
    char *escaped = str_escape((char *) "ABC\\", (char *) "AB");
    g_assert_cmpstr(escaped, ==, "\\A\\BC\\\\");
    free(escaped);
}

static void test_str_unescape_1() {
    char *unescaped = str_unescape((char *) "");
    g_assert_cmpstr(unescaped, ==, "");
    free(unescaped);
}

static void test_str_unescape_2() {
    char *unescaped = str_unescape((char *) "Sport Club Corinthians Paulista");
    g_assert_cmpstr(unescaped, ==, (char *) "Sport Club Corinthians Paulista"); 
    free(unescaped);
}

static void test_str_unescape_3() {
    char *unescaped = str_unescape((char *) "\\\\");
    g_assert_cmpstr(unescaped, ==, "\\");
    free(unescaped);
}

static void test_str_unescape_4() {
    char *unescaped = str_unescape((char *) "\\\\Sport Club \\Corinthians Paulista");
    g_assert_cmpstr(unescaped, ==, "\\Sport Club Corinthians Paulista");
    free(unescaped);
}

static void test_str_find_1() {
    g_assert_cmpint(str_find((char *) "x", (char *) ""), ==, -1);
}

static void test_str_find_2() {
    g_assert_cmpint(str_find((char *) "x", (char *) "a"), ==, -1);
}

static void test_str_find_3() {
    g_assert_cmpint(str_find((char *) "x", (char *) "x"), ==, 0);
}

static void test_str_find_4() {
    g_assert_cmpint(str_find((char *) "xx", (char *) "x"), ==, 0);
}

static void test_str_find_5() {
    g_assert_cmpint(str_find((char *) "Sport Club Corinthians Paulista", (char *) "Sport"), ==,
                    0);
}

static void test_str_find_6() {
    g_assert_cmpint(str_find((char *) "Sport Club Corinthians Paulista",
                             (char *) "Corinthians"), ==, 11);
}

static void test_str_join_1() {
    ADTList strs = list_new();
    char *join = str_join(strs, (char *) "");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_2() {
    ADTList strs = list_new();
    char *join = str_join(strs, (char *) "abc");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_3() {
    ADTList strs = list_new();
    list_append(strs, (char *) "");
    char *join = str_join(strs, (char *) "");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_4() {
    ADTList strs = list_new();
    list_append(strs, (char *) "");
    char *join = str_join(strs, (char *) "abc");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_5() {
    ADTList strs = list_new();
    list_append(strs, (char *) "");
    list_append(strs, (char *) "");
    char *join = str_join(strs, (char *) "abc");
    g_assert_cmpstr(join, ==, "abc");
    list_release(strs);
    free(join);
}

static void test_str_join_6() {
    ADTList strs = list_new();
    list_append(strs, (char *) "Sport Club Corinthians Paulista");
    char *join = str_join(strs, (char *) "");
    g_assert_cmpstr(join, ==, (char *) "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_7() {
    ADTList strs = list_new();
    list_append(strs, (char *) "Sport Club Corinthians Paulista");
    char *join = str_join(strs, (char *) "abc");
    g_assert_cmpstr(join, ==, (char *) "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_8() {
    ADTList strs = list_new();
    list_append(strs, (char *) "Sport");
    list_append(strs, (char *) "Club");
    list_append(strs, (char *) "Corinthians");
    list_append(strs, (char *) "Paulista");
    char *join = str_join(strs, (char *) " ");
    g_assert_cmpstr(join, ==, (char *) "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_9() {
    ADTList strs = list_new();
    list_append(strs, (char *) "Sport");
    list_append(strs, (char *) "Club");
    list_append(strs, (char *) "Corinthians");
    list_append(strs, (char *) "Paulista");
    char *join = str_join(strs, (char *) "___");
    g_assert_cmpstr(join, ==, "Sport___Club___Corinthians___Paulista");
    list_release(strs);
    free(join);
}

static void test_str_split_1() {
    ADTList split = str_split((char *) "", (char *) "");
    ADTList result = list_new();
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(split);
    list_release(result);
}

static void test_str_split_2() {
    ADTList split = str_split((char *) "abc", (char *) "");
    ADTList result = list_new();
    list_append(result, (char *) "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_3() {
    ADTList split = str_split((char *) "abc", (char *) "___");
    ADTList result = list_new();
    list_append(result, (char *) "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_4() {
    ADTList split = str_split((char *) "___abc", (char *) "___");
    ADTList result = list_new();
    list_append(result, (char *) "");
    list_append(result, (char *) "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_5() {
    ADTList split = str_split((char *) "abc___", (char *) "___");
    ADTList result = list_new();
    list_append(result, (char *) "abc");
    list_append(result, (char *) "");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_6() {
    ADTList split = str_split((char *) "abc___def", (char *) "___");
    ADTList result = list_new();
    list_append(result, (char *) "abc");
    list_append(result, (char *) "def");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_7() {
    ADTList split = str_split((char *) "abc___def___ghi", (char *) "___");
    ADTList result = list_new();
    list_append(result, (char *) "abc");
    list_append(result, (char *) "def");
    list_append(result, (char *) "ghi");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_8() {
    ADTList split = str_split((char *) "Sport Club Corinthians Paulista", (char *) " ");
    ADTList result = list_new();
    list_append(result, (char *) "Sport");
    list_append(result, (char *) "Club");
    list_append(result, (char *) "Corinthians");
    list_append(result, (char *) "Paulista");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/str/equals", test_str_equals_1);
    g_test_add_func("/str/equals", test_str_equals_2);
    g_test_add_func("/str/equals", test_str_equals_3);
    g_test_add_func("/str/dup", test_str_dup_1);
    g_test_add_func("/str/dup", test_str_dup_2);
    g_test_add_func("/str/random", test_str_random_1);
    g_test_add_func("/str/random", test_str_random_2);
    g_test_add_func("/str/substr", test_str_substr_1);
    g_test_add_func("/str/substr", test_str_substr_2);
    g_test_add_func("/str/substr", test_str_substr_3);
    g_test_add_func("/str/cat", test_str_cat_1);
    g_test_add_func("/str/cat", test_str_cat_2);
    g_test_add_func("/str/reverse", test_str_reverse_1);
    g_test_add_func("/str/reverse", test_str_reverse_2);
    g_test_add_func("/str/escape", test_str_escape_1);
    g_test_add_func("/str/escape", test_str_escape_2);
    g_test_add_func("/str/escape", test_str_escape_3);
    g_test_add_func("/str/escape", test_str_escape_4);
    g_test_add_func("/str/escape", test_str_escape_5);
    g_test_add_func("/str/unescape", test_str_unescape_1);
    g_test_add_func("/str/unescape", test_str_unescape_2);
    g_test_add_func("/str/unescape", test_str_unescape_3);
    g_test_add_func("/str/unescape", test_str_unescape_4);
    g_test_add_func("/str/find", test_str_find_1);
    g_test_add_func("/str/find", test_str_find_2);
    g_test_add_func("/str/find", test_str_find_3);
    g_test_add_func("/str/find", test_str_find_4);
    g_test_add_func("/str/find", test_str_find_5);
    g_test_add_func("/str/find", test_str_find_6);
    g_test_add_func("/str/join", test_str_join_1);
    g_test_add_func("/str/join", test_str_join_2);
    g_test_add_func("/str/join", test_str_join_3);
    g_test_add_func("/str/join", test_str_join_4);
    g_test_add_func("/str/join", test_str_join_5);
    g_test_add_func("/str/join", test_str_join_6);
    g_test_add_func("/str/join", test_str_join_7);
    g_test_add_func("/str/join", test_str_join_8);
    g_test_add_func("/str/join", test_str_join_9);
    g_test_add_func("/str/split", test_str_split_1);
    g_test_add_func("/str/split", test_str_split_2);
    g_test_add_func("/str/split", test_str_split_3);
    g_test_add_func("/str/split", test_str_split_4);
    g_test_add_func("/str/split", test_str_split_5);
    g_test_add_func("/str/split", test_str_split_6);
    g_test_add_func("/str/split", test_str_split_7);
    g_test_add_func("/str/split", test_str_split_8);
    return g_test_run();
}

