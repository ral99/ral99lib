#include <glib.h>
#include <stdlib.h>
#include <string.h>

#include "net/net.h"
#include "adt/adt.h"
#include "str/str.h"

#define POLL_TIMEOUT 500

static void test_accept_server_connection_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert_cmpint(strlen(server_connection->id), ==, SERVER_CONNECTION_ID_LENGTH);
    g_assert_cmpint(connection_is_on(server_connection->connection), ==, 1);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_release_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_get_id_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert(server_connection_get_id(server_connection) == server_connection->id);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_set_id_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    char *id = str_random(SERVER_CONNECTION_ID_LENGTH);
    free(server_connection->id);
    server_connection_set_id(server_connection, id);
    g_assert(server_connection->id == id);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_get_connection_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert(server_connection_get_connection(server_connection) ==
             server_connection->connection);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_set_connection_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected1 = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    Connection connected2 = connection_connect(address);
    Connection connection = connection_accept(server);
    connection_release(server_connection->connection);
    server_connection_set_connection(server_connection, connection);
    g_assert(server_connection->connection == connection);
    server_connection_release(server_connection);
    connection_release(connected1);
    connection_release(connected2);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_id_is_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert_cmpint(server_connection_id_is(server_connection, "abc"), ==, 0);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_id_is_2() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    char *id = str_dup(server_connection->id);
    g_assert_cmpint(server_connection_id_is(server_connection, id), ==, 1);
    free(id);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_id_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    char *id = server_connection_id(server_connection);
    g_assert_cmpstr(id, ==, server_connection->id);
    free(id);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_is_on_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert_cmpint(server_connection_is_on(server_connection), ==, 1);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_is_on_2() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    connection_turn_off(server_connection->connection);
    g_assert_cmpint(server_connection_is_on(server_connection), ==, 0);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_is_off_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    g_assert_cmpint(server_connection_is_off(server_connection), ==, 0);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_is_off_2() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    connection_turn_off(server_connection->connection);
    g_assert_cmpint(server_connection_is_off(server_connection), ==, 1);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_turn_off_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    server_connection_turn_off(server_connection);
    g_assert_cmpint(connection_is_off(server_connection->connection), ==, 1);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_out_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    connection_push(server_connection->connection,
                    "Sport Club Corinthians Paulista");
    connection_push(server_connection->connection, "Republica Federativa do Brasil");
    List out1 = connection_out(server_connection->connection);
    List out2 = server_connection_out(server_connection);
    g_assert_cmpint(list_equals_cmp(out1, out2,
                                    (int (*)(void *, void *)) str_equals), ==, 1);
    list_full_release(out1, free);
    list_full_release(out2, free);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_push_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    server_connection_push(server_connection, "Sport Club Corinthians Paulista");
    List out = connection_out(server_connection->connection);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_pop_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected = connection_connect(address);
    ServerConnection server_connection = accept_server_connection(server);
    connection_push(connected, "Sport Club Corinthians Paulista");
    connection_loop(connected);
    connection_loop(server_connection->connection);
    char *text = server_connection_pop(server_connection);
    g_assert_cmpstr(text, ==, "Sport Club Corinthians Paulista");
    g_assert(server_connection_pop(server_connection) == NULL);
    free(text);
    server_connection_release(server_connection);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_loop_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected1 = connection_connect(address);
    ServerConnection server_connection1 = accept_server_connection(server);
    Connection connected2 = connection_connect(address);
    ServerConnection server_connection2 = accept_server_connection(server);
    Connection connected3 = connection_connect(address);
    ServerConnection server_connection3 = accept_server_connection(server);
    connection_push(connected1, "Sport Club Corinthians Paulista");
    connection_push(connected2, "Republica Federativa do Brasil");
    connection_push(connected3, "Repubblica Italiana");
    connection_push(server_connection1->connection,
                    "Republica Federativa do Brasil");
    connection_push(server_connection2->connection, "Repubblica Italiana");
    connection_push(server_connection3->connection,
                    "Sport Club Corinthians Paulista");
    for (int i = 0; i < 2; i++) {
        connection_loop(connected1);
        connection_loop(connected2);
        connection_loop(connected3);
        server_connection_loop(server_connection1);
        server_connection_loop(server_connection2);
        server_connection_loop(server_connection3);
    }
    List out1 = connection_out(server_connection1->connection);
    List out2 = connection_out(server_connection2->connection);
    List out3 = connection_out(server_connection3->connection);
    g_assert_cmpint(list_size(out1), ==, 0);
    g_assert_cmpint(list_size(out2), ==, 0);
    g_assert_cmpint(list_size(out3), ==, 0);
    list_release(out1);
    list_release(out2);
    list_release(out3);
    char *text1 = connection_pop(connected1);
    char *text2 = connection_pop(connected2);
    char *text3 = connection_pop(connected3);
    char *text4 = connection_pop(server_connection1->connection);
    char *text5 = connection_pop(server_connection2->connection);
    char *text6 = connection_pop(server_connection3->connection);
    g_assert(connection_pop(connected1) == NULL);
    g_assert(connection_pop(connected2) == NULL);
    g_assert(connection_pop(connected3) == NULL);
    g_assert(connection_pop(server_connection1->connection) == NULL);
    g_assert(connection_pop(server_connection2->connection) == NULL);
    g_assert(connection_pop(server_connection3->connection) == NULL);
    g_assert_cmpstr(text1, ==, "Republica Federativa do Brasil");
    g_assert_cmpstr(text2, ==, "Repubblica Italiana");
    g_assert_cmpstr(text3, ==, "Sport Club Corinthians Paulista");
    g_assert_cmpstr(text4, ==, "Sport Club Corinthians Paulista");
    g_assert_cmpstr(text5, ==, "Republica Federativa do Brasil");
    g_assert_cmpstr(text6, ==, "Repubblica Italiana");
    free(text1);
    free(text2);
    free(text3);
    free(text4);
    free(text5);
    free(text6);
    server_connection_release(server_connection1);
    server_connection_release(server_connection2);
    server_connection_release(server_connection3);
    connection_release(connected1);
    connection_release(connected2);
    connection_release(connected3);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_list_poll_1() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected1 = connection_connect(address);
    ServerConnection server_connection1 = accept_server_connection(server);
    Connection connected2 = connection_connect(address);
    ServerConnection server_connection2 = accept_server_connection(server);
    List server_connections = list_new();
    list_append(server_connections, server_connection1);
    list_append(server_connections, server_connection2);
    g_assert_cmpint(server_connection_list_poll(server_connections, POLL_TIMEOUT),
                    ==, 0);
    list_release(server_connections);
    server_connection_release(server_connection1);
    server_connection_release(server_connection2);
    connection_release(connected1);
    connection_release(connected2);
    sock_release(server);
    address_release(address);
}

static void test_server_connection_list_poll_2() {
    Address address = address_new("127.0.0.1", 5000);
    Sock server = sock_listen(5000);
    Connection connected1 = connection_connect(address);
    ServerConnection server_connection1 = accept_server_connection(server);
    Connection connected2 = connection_connect(address);
    ServerConnection server_connection2 = accept_server_connection(server);
    List server_connections = list_new();
    list_append(server_connections, server_connection1);
    list_append(server_connections, server_connection2);
    connection_push(server_connection1->connection,
                    "Sport Club Corinthians Paulista");
    g_assert_cmpint(server_connection_list_poll(server_connections, POLL_TIMEOUT),
                    ==, 1);
    list_release(server_connections);
    server_connection_release(server_connection1);
    server_connection_release(server_connection2);
    connection_release(connected1);
    connection_release(connected2);
    sock_release(server);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/server_connection/accept", test_accept_server_connection_1);
    g_test_add_func("/server_connection/release", test_server_connection_release_1);
    g_test_add_func("/server_connection/get_id", test_server_connection_get_id_1);
    g_test_add_func("/server_connection/set_id", test_server_connection_set_id_1);
    g_test_add_func("/server_connection/get_connection",
                    test_server_connection_get_connection_1);
    g_test_add_func("/server_connection/set_connection",
                    test_server_connection_set_connection_1);
    g_test_add_func("/server_connection/id_is", test_server_connection_id_is_1);
    g_test_add_func("/server_connection/id_is", test_server_connection_id_is_2);
    g_test_add_func("/server_conenction/id", test_server_connection_id_1);
    g_test_add_func("/server_connection/is_on", test_server_connection_is_on_1);
    g_test_add_func("/server_connection/is_on", test_server_connection_is_on_2);
    g_test_add_func("/server_connection/is_off", test_server_connection_is_off_1);
    g_test_add_func("/server_connection/is_off", test_server_connection_is_off_2);
    g_test_add_func("/server_connection/turn_off",
                    test_server_connection_turn_off_1);
    g_test_add_func("/server_connection/out", test_server_connection_out_1);
    g_test_add_func("/server_connection/push", test_server_connection_push_1);
    g_test_add_func("/server_connection/pop", test_server_connection_pop_1);
    g_test_add_func("/server_connection/loop", test_server_connection_loop_1);
    g_test_add_func("/server_connection/list_poll",
                    test_server_connection_list_poll_1);
    g_test_add_func("/server_connection/list_poll",
                    test_server_connection_list_poll_2);
    return g_test_run();
}

