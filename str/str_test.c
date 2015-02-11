#include <glib.h>
#include <stdlib.h>
#include <string.h>

#include "str/str.h"
#include "adt/adt.h"

static void test_str_equals_1() {
    g_assert_cmpint(str_equals("", ""), ==, 1);
}

static void test_str_equals_2() {
    g_assert_cmpint(str_equals("Sport Club Corinthians Paulista",
                               "Sport Club Corinthians Paulista"), ==, 1);
}

static void test_str_equals_3() {
    g_assert_cmpint(str_equals("Sport Club Corinthians Paulista",
                               "Republica Oriental del Uruguay"), ==, 0);
}

static void test_str_dup_1() {
    char *dup = str_dup("");
    g_assert_cmpstr(dup, ==, "");
    free(dup);
}

static void test_str_dup_2() {
    char *dup = str_dup("Sport Club Corinthians Paulista");
    g_assert_cmpstr(dup, ==, "Sport Club Corinthians Paulista");
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
    g_assert_cmpint(strlen(str), ==, len);
    for (int i = 0; i < len; i++)
        g_assert((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] >= 'A' && str[i] <= 'Z'));
    free(str);
}

static void test_str_substr_1() {
    char *substr = str_substr("", 0, 0);
    g_assert_cmpstr(substr, ==, "");
    free(substr);
}

static void test_str_substr_2() {
    char *substr = str_substr("Sport Club Corinthians Paulista", 0, 5);
    g_assert_cmpstr(substr, ==, "Sport");
    free(substr);
}

static void test_str_substr_3() {
    char *substr = str_substr("Sport Club Corinthians Paulista", 11, 11);
    g_assert_cmpstr(substr, ==, "Corinthians");
    free(substr);
}

static void test_str_cat_1() {
    char *cat = str_cat("", "");
    g_assert_cmpstr(cat, ==, "");
    free(cat);
}

static void test_str_cat_2() {
    char *cat = str_cat("Sport Club ", "Corinthians Paulista");
    g_assert_cmpstr(cat, ==, "Sport Club Corinthians Paulista");
    free(cat);
}

static void test_str_reverse_1() {
    char *reversed = str_reverse("");
    g_assert_cmpstr(reversed, ==, "");
    free(reversed);
}

static void test_str_reverse_2() {
    char *reversed = str_reverse("12345");
    g_assert_cmpstr(reversed, ==, "54321");
    free(reversed);
}

static void test_str_escape_1() {
    char *escaped = str_escape("", "");
    g_assert_cmpstr(escaped, ==, "");
    free(escaped);
}

static void test_str_escape_2() {
    char *escaped = str_escape("Sport Club Corinthians Paulista", "");
    g_assert_cmpstr(escaped, ==, "Sport Club Corinthians Paulista");
    free(escaped);
}

static void test_str_escape_3() {
    char *escaped = str_escape("\\Sport Clu\\b Corinthians Pau\\lista", "");
    g_assert_cmpstr(escaped, ==, "\\\\Sport Clu\\\\b Corinthians Pau\\\\lista");
    free(escaped);
}

static void test_str_escape_4() {
    char *escaped = str_escape("A", "A");
    g_assert_cmpstr(escaped, ==, "\\A");
    free(escaped);
}

static void test_str_escape_5() {
    char *escaped = str_escape("ABC\\", "AB");
    g_assert_cmpstr(escaped, ==, "\\A\\BC\\\\");
    free(escaped);
}

static void test_str_unescape_1() {
    char *unescaped = str_unescape("");
    g_assert_cmpstr(unescaped, ==, "");
    free(unescaped);
}

static void test_str_unescape_2() {
    char *unescaped = str_unescape("Sport Club Corinthians Paulista");
    g_assert_cmpstr(unescaped, ==, "Sport Club Corinthians Paulista"); 
    free(unescaped);
}

static void test_str_unescape_3() {
    char *unescaped = str_unescape("\\\\");
    g_assert_cmpstr(unescaped, ==, "\\");
    free(unescaped);
}

static void test_str_unescape_4() {
    char *unescaped = str_unescape("\\\\Sport Club \\Corinthians Paulista");
    g_assert_cmpstr(unescaped, ==, "\\Sport Club Corinthians Paulista");
    free(unescaped);
}

static void test_str_find_1() {
    g_assert_cmpint(str_find("x", ""), ==, -1);
}

static void test_str_find_2() {
    g_assert_cmpint(str_find("x", "a"), ==, -1);
}

static void test_str_find_3() {
    g_assert_cmpint(str_find("x", "x"), ==, 0);
}

static void test_str_find_4() {
    g_assert_cmpint(str_find("xx", "x"), ==, 0);
}

static void test_str_find_5() {
    g_assert_cmpint(str_find("Sport Club Corinthians Paulista", "Sport"), ==, 0);
}

static void test_str_find_6() {
    g_assert_cmpint(str_find("Sport Club Corinthians Paulista", "Corinthians"), ==, 11);
}

static void test_str_join_1() {
    ADTList strs = list_new();
    char *join = str_join(strs, "");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_2() {
    ADTList strs = list_new();
    char *join = str_join(strs, "abc");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_3() {
    ADTList strs = list_new();
    list_append(strs, "");
    char *join = str_join(strs, "");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_4() {
    ADTList strs = list_new();
    list_append(strs, "");
    char *join = str_join(strs, "abc");
    g_assert_cmpstr(join, ==, "");
    list_release(strs);
    free(join);
}

static void test_str_join_5() {
    ADTList strs = list_new();
    list_append(strs, "");
    list_append(strs, "");
    char *join = str_join(strs, "abc");
    g_assert_cmpstr(join, ==, "abc");
    list_release(strs);
    free(join);
}

static void test_str_join_6() {
    ADTList strs = list_new();
    list_append(strs, "Sport Club Corinthians Paulista");
    char *join = str_join(strs, "");
    g_assert_cmpstr(join, ==, "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_7() {
    ADTList strs = list_new();
    list_append(strs, "Sport Club Corinthians Paulista");
    char *join = str_join(strs, "abc");
    g_assert_cmpstr(join, ==, "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_8() {
    ADTList strs = list_new();
    list_append(strs, "Sport");
    list_append(strs, "Club");
    list_append(strs, "Corinthians");
    list_append(strs, "Paulista");
    char *join = str_join(strs, " ");
    g_assert_cmpstr(join, ==, "Sport Club Corinthians Paulista");
    list_release(strs);
    free(join);
}

static void test_str_join_9() {
    ADTList strs = list_new();
    list_append(strs, "Sport");
    list_append(strs, "Club");
    list_append(strs, "Corinthians");
    list_append(strs, "Paulista");
    char *join = str_join(strs, "___");
    g_assert_cmpstr(join, ==, "Sport___Club___Corinthians___Paulista");
    list_release(strs);
    free(join);
}

static void test_str_split_1() {
    ADTList split = str_split("", "");
    ADTList result = list_new();
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_release(split);
    list_release(result);
}

static void test_str_split_2() {
    ADTList split = str_split("abc", "");
    ADTList result = list_new();
    list_append(result, "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_3() {
    ADTList split = str_split("abc", "___");
    ADTList result = list_new();
    list_append(result, "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_4() {
    ADTList split = str_split("___abc", "___");
    ADTList result = list_new();
    list_append(result, "");
    list_append(result, "abc");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_5() {
    ADTList split = str_split("abc___", "___");
    ADTList result = list_new();
    list_append(result, "abc");
    list_append(result, "");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_6() {
    ADTList split = str_split("abc___def", "___");
    ADTList result = list_new();
    list_append(result, "abc");
    list_append(result, "def");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_7() {
    ADTList split = str_split("abc___def___ghi", "___");
    ADTList result = list_new();
    list_append(result, "abc");
    list_append(result, "def");
    list_append(result, "ghi");
    g_assert_cmpint(list_equals_cmp(split, result, (int (*)(void *, void *)) str_equals), ==,
                    1);
    list_full_release(split, free);
    list_release(result);
}

static void test_str_split_8() {
    ADTList split = str_split("Sport Club Corinthians Paulista", " ");
    ADTList result = list_new();
    list_append(result, "Sport");
    list_append(result, "Club");
    list_append(result, "Corinthians");
    list_append(result, "Paulista");
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

