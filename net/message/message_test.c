#include <glib.h>
#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "str/str.h"

static void test_message_new_1() {
    Message message = message_new("123", "abc");
    g_assert_cmpstr(message->id, ==, "123");
    g_assert_cmpstr(message->text, ==, "abc");
    message_release(message);
}

static void test_message_release_1() {
    Message message = message_new("123", "abc");
    message_release(message);
}

static void test_message_equals_1() {
    Message message1 = message_new("123", "abc");
    Message message2 = message_new("123", "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_2() {
    Message message1 = message_new("123", "abc");
    Message message2 = message_new("123", "ABC");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_3() {
    Message message1 = message_new("123", "abc");
    Message message2 = message_new("456", "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_equals_4() {
    Message message1 = message_new("123", "abc");
    Message message2 = message_new("456", "ABC");
    g_assert_cmpint(message_equals(message1, message2), ==, 0);
    message_release(message1);
    message_release(message2);
}

static void test_message_to_str_1() {
    Message message = message_new("123", "abc");
    char *str = message_to_str(message);
    g_assert_cmpstr(str, ==, "123,abc");
    free(str);
    message_release(message);
}

static void test_message_to_str_2() {
    Message message = message_new("123,456,789", "abc,def,ghi");
    char *str = message_to_str(message);
    g_assert_cmpstr(str, ==, "123\\,456\\,789,abc\\,def\\,ghi");
    free(str);
    message_release(message);
}

static void test_message_from_str_1() {
    Message message1 = message_from_str("123,abc");
    Message message2 = message_new("123", "abc");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_from_str_2() {
    Message message1 = message_from_str("123\\,456\\,789,abc\\,def\\,ghi");
    Message message2 = message_new("123,456,789", "abc,def,ghi");
    g_assert_cmpint(message_equals(message1, message2), ==, 1);
    message_release(message1);
    message_release(message2);
}

static void test_message_dup_1() {
    Message message = message_new("123", "abc");
    Message dup = message_dup(message);
    g_assert_cmpint(message_equals(message, dup), ==, 1);
    message_release(message);
    message_release(dup);
}

static void test_message_get_id_1() {
    Message message = message_new("123", "abc");
    g_assert(message_get_id(message) == message->id);
    message_release(message);
}

static void test_message_set_id_1() {
    Message message = message_new("123", "abc");
    char *id = str_dup("123");
    free(message->id);
    message_set_id(message, id);
    g_assert(message->id == id);
    message_release(message);
}

static void test_message_get_text_1() {
    Message message = message_new("123", "abc");
    g_assert(message_get_text(message) == message->text);
    message_release(message);
}

static void test_message_set_text_1() {
    Message message = message_new("123", "abc");
    char *text = str_dup("abc");
    free(message->text);
    message_set_text(message, text);
    g_assert(message->text == text);
    message_release(message);
}

static void test_message_id_is_1() {
    Message message = message_new("123", "abc");
    g_assert_cmpint(message_id_is(message, "123"), ==, 1);
    message_release(message);
}

static void test_message_id_is_2() {
    Message message = message_new("123", "abc");
    g_assert_cmpint(message_id_is(message, "1234"), ==, 0);
    message_release(message);
}

static void test_message_text_is_1() {
    Message message = message_new("123", "abc");
    g_assert_cmpint(message_text_is(message, "abc"), ==, 1);
    message_release(message);
}

static void test_message_text_is_2() {
    Message message = message_new("123", "abc");
    g_assert_cmpint(message_text_is(message, "abcd"), ==, 0);
    message_release(message);
}

static void test_message_id_1() {
    Message message = message_new("123", "abc");
    char *id = message_id(message);
    g_assert_cmpstr(id, ==, "123");
    free(id);
    message_release(message);
}

static void test_message_text_1() {
    Message message = message_new("123", "abc");
    char *text = message_text(message);
    g_assert_cmpstr(text, ==, "abc");
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

