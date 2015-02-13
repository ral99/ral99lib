#include <glib.h>
#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "str/str.h"

static void test_message_new_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert_cmpstr(message->id, ==, "123");
    g_assert_cmpstr(message->text, ==, (char *) "abc");
    message_release(message);
}

static void test_message_release_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    message_release(message);
}

static void test_message_equals_1() {
    NETMessage message1 = message_new((char *) "123", (char *) "abc");
    NETMessage message2 = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_2() {
    NETMessage message1 = message_new((char *) "123", (char *) "abc");
    NETMessage message2 = message_new((char *) "123", (char *) "ABC");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_3() {
    NETMessage message1 = message_new((char *) "123", (char *) "abc");
    NETMessage message2 = message_new((char *) "456", (char *) "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_4() {
    NETMessage message1 = message_new((char *) "123", (char *) "abc");
    NETMessage message2 = message_new((char *) "456", (char *) "ABC");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_to_str_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    char *str = message_to_str(message);
    g_assert_cmpstr(str, ==, "123,abc");
    free(str);
    message_release(message);
}

static void test_message_to_str_2() {
    NETMessage message = message_new((char *) "123,456,789", (char *) "abc,def,ghi");
    char *str = message_to_str(message);
    g_assert_cmpstr(str, ==, "123\\,456\\,789,abc\\,def\\,ghi");
    free(str);
    message_release(message);
}

static void test_message_from_str_1() {
    NETMessage message1 = message_from_str((char *) "123,abc");
    NETMessage message2 = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_from_str_2() {
    NETMessage message1 = message_from_str((char *) "123\\,456\\,789,abc\\,def\\,ghi");
    NETMessage message2 = message_new((char *) "123,456,789", (char *) "abc,def,ghi");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_dup_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    NETMessage dup = message_dup(message);
    g_assert_cmpint(message_equals(message, dup), ==, 1);
    message_release(message);
    message_release(dup);
}

static void test_message_get_id_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert(message_get_id(message) == message->id);
    message_release(message);
}

static void test_message_set_id_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    char *id = str_dup((char *) "123");
    free(message->id);
    message_set_id(message, id);
    g_assert(message->id == id);
    message_release(message);
}

static void test_message_get_text_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert(message_get_text(message) == message->text);
    message_release(message);
}

static void test_message_set_text_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    char *text = str_dup((char *) "abc");
    free(message->text);
    message_set_text(message, text);
    g_assert(message->text == text);
    message_release(message);
}

static void test_message_id_is_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_id_is(message, (char *) "123"), ==, 1);
    message_release(message);
}

static void test_message_id_is_2() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_id_is(message, (char *) "1234"), ==, 0);
    message_release(message);
}

static void test_message_text_is_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_text_is(message, (char *) "abc"), ==, 1);
    message_release(message);
}

static void test_message_text_is_2() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    g_assert_cmpint(message_text_is(message, (char *) "abcd"), ==, 0);
    message_release(message);
}

static void test_message_id_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    char *id = message_id(message);
    g_assert_cmpstr(id, ==, "123");
    free(id);
    message_release(message);
}

static void test_message_text_1() {
    NETMessage message = message_new((char *) "123", (char *) "abc");
    char *text = message_text(message);
    g_assert_cmpstr(text, ==, (char *) "abc");
    free(text);
    message_release(message);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/message/new", test_message_new_1);
    g_test_add_func("/message/release", test_message_release_1);
    g_test_add_func("/message/equals", test_message_equals_1);
    g_test_add_func("/message/equals", test_message_equals_2);
    g_test_add_func("/message/equals", test_message_equals_3);
    g_test_add_func("/message/equals", test_message_equals_4);
    g_test_add_func("/message/to_str", test_message_to_str_1);
    g_test_add_func("/message/to_str", test_message_to_str_2);
    g_test_add_func("/message/from_str", test_message_from_str_1);
    g_test_add_func("/message/from_str", test_message_from_str_2);
    g_test_add_func("/message/dup", test_message_dup_1);
    g_test_add_func("/message/get_id", test_message_get_id_1);
    g_test_add_func("/message/set_id", test_message_set_id_1);
    g_test_add_func("/message/get_text", test_message_get_text_1);
    g_test_add_func("/message/set_text", test_message_set_text_1);
    g_test_add_func("/message/id_is", test_message_id_is_1);
    g_test_add_func("/message/id_is", test_message_id_is_2);
    g_test_add_func("/message/text_is", test_message_text_is_1);
    g_test_add_func("/message/text_is", test_message_text_is_2);
    g_test_add_func("/message/id", test_message_id_1);
    g_test_add_func("/message/text", test_message_text_1);
    return g_test_run();
}

