#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "net/net.h"
#include "adt/adt.h"
#include "str/str.h"

#define POLL_TIMEOUT 500

static void test_connect_client_connection_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert_cmpint(address_equals(client_connection->address, address), ==, 1);
    g_assert_cmpint(connection_is_on(client_connection->connection), ==, 1);
    g_assert(client_connection->expires >= time(NULL) + 3 &&
             client_connection->expires <= time(NULL) + 5);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_release_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_get_address_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert(client_connection_get_address(client_connection) ==
             client_connection->address);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_set_address_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    address_release(client_connection->address);
    client_connection_set_address(client_connection, address);
    g_assert(client_connection->address == address);
    client_connection_release(client_connection);
}

static void test_client_connection_get_connection_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert(client_connection_get_connection(client_connection) ==
             client_connection->connection);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_set_connection_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    NETConnection connection = connection_connect(address);
    connection_release(client_connection->connection);
    client_connection_set_connection(client_connection, connection);
    g_assert(client_connection->connection == connection);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_get_expires_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert(client_connection_get_expires(client_connection) ==
             client_connection->expires);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_set_expires_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 10);
    time_t expires = time(NULL) + 5;
    client_connection_set_expires(client_connection, expires);
    g_assert(client_connection->expires == expires);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_address_is_1() {
    NETAddress address1 = address_new("127.0.0.1", 5000);
    NETAddress address2 = address_dup(address1);
    NETClientConnection client_connection = connect_client_connection(address1, 5);
    g_assert_cmpint(client_connection_address_is(client_connection, address2), ==,
                    1);
    client_connection_release(client_connection);
    address_release(address1);
    address_release(address2);
}

static void test_client_connection_address_is_2() {
    NETAddress address1 = address_new("127.0.0.1", 5000);
    NETAddress address2 = address_new("127.0.0.1", 5001);
    NETClientConnection client_connection = connect_client_connection(address1, 5);
    g_assert_cmpint(client_connection_address_is(client_connection, address2), ==,
                    0);
    client_connection_release(client_connection);
    address_release(address1);
    address_release(address2);
}

static void test_client_connection_is_alive_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert_cmpint(client_connection_is_alive(client_connection), ==, 1);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_alive_2() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 0);
    g_assert_cmpint(client_connection_is_alive(client_connection), ==, 0);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_dead_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert_cmpint(client_connection_is_dead(client_connection), ==, 0);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_dead_2() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 0);
    g_assert_cmpint(client_connection_is_dead(client_connection), ==, 1);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_on_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert_cmpint(client_connection_is_on(client_connection), ==, 1);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_on_2() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    connection_turn_off(client_connection->connection);
    g_assert_cmpint(client_connection_is_on(client_connection), ==, 0);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_off_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    g_assert_cmpint(client_connection_is_off(client_connection), ==, 0);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_is_off_2() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    connection_turn_off(client_connection->connection);
    g_assert_cmpint(client_connection_is_off(client_connection), ==, 1);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_turn_on_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    connection_push(client_connection->connection,
                    "Sport Club Corinthians Paulista");
    connection_turn_off(client_connection->connection);
    client_connection_turn_on(client_connection);
    ADTList out = connection_out(client_connection->connection);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    g_assert_cmpint(connection_is_on(client_connection->connection), ==, 1);
    list_full_release(out, free);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_turn_off_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    client_connection_turn_off(client_connection);
    g_assert_cmpint(connection_is_off(client_connection->connection), ==, 1);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_lasts_for_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 0);
    client_connection_lasts_for(client_connection, 5);
    g_assert(client_connection->expires >= time(NULL) + 3 &&
             client_connection->expires <= time(NULL) + 5);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_out_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 0);
    connection_push(client_connection->connection,
                    "Sport Club Corinthians Paulista");
    connection_push(client_connection->connection, "Republica Federativa do Brasil");
    ADTList out1 = connection_out(client_connection->connection);
    ADTList out2 = client_connection_out(client_connection);
    g_assert_cmpint(list_equals_cmp(out1, out2,
                                    (int (*)(void *, void *)) str_equals), ==, 1);
    list_full_release(out1, free);
    list_full_release(out2, free);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_push_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    client_connection_push(client_connection, "Sport Club Corinthians Paulista");
    ADTList out = connection_out(client_connection->connection);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    client_connection_release(client_connection);
    address_release(address);
}

static void test_client_connection_loop_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETClientConnection client_connection1 = connect_client_connection(address, 60);
    sleep(1);
    NETConnection accepted1 = connection_accept(server);
    sleep(1);
    NETClientConnection client_connection2 = connect_client_connection(address, 60);
    sleep(1);
    NETConnection accepted2 = connection_accept(server);
    sleep(1);
    NETClientConnection client_connection3 = connect_client_connection(address, 60);
    sleep(1);
    NETConnection accepted3 = connection_accept(server);
    connection_push(client_connection1->connection, "Repubblica Italiana");
    connection_push(client_connection2->connection,
                    "Sport Club Corinthians Paulista");
    connection_push(client_connection3->connection,
                    "Republica Federativa do Brasil");
    connection_turn_off(client_connection3->connection);
    client_connection_loop(client_connection3);
    sleep(1);
    NETConnection accepted4 = connection_accept(server);
    sleep(1);
    connection_push(accepted1, "Sport Club Corinthians Paulista");
    connection_push(accepted2, "Republica Federativa do Brasil");
    connection_push(accepted4, "Repubblica Italiana");
    for (int i = 0; i < 2; i++) {
        connection_loop(accepted1);
        connection_loop(accepted2);
        connection_loop(accepted4);
        client_connection_loop(client_connection1);
        client_connection_loop(client_connection2);
        client_connection_loop(client_connection3);
        sleep(1);
    }
    g_assert(connection_pop(client_connection1->connection) == NULL);
    g_assert(connection_pop(client_connection2->connection) == NULL);
    g_assert(connection_pop(client_connection3->connection) == NULL);
    char *text1 = connection_pop(accepted1);
    char *text2 = connection_pop(accepted2);
    char *text3 = connection_pop(accepted4);
    g_assert_cmpstr(text1, ==, "Repubblica Italiana");
    g_assert_cmpstr(text2, ==, "Sport Club Corinthians Paulista");
    g_assert_cmpstr(text3, ==, "Republica Federativa do Brasil");
    free(text1);
    free(text2);
    free(text3);
    g_assert(connection_pop(accepted1) == NULL);
    g_assert(connection_pop(accepted2) == NULL);
    g_assert(connection_pop(accepted4) == NULL);
    connection_release(accepted1);
    connection_release(accepted2);
    connection_release(accepted3);
    connection_release(accepted4);
    client_connection_release(client_connection1);
    client_connection_release(client_connection2);
    client_connection_release(client_connection3);
    sock_release(server);
    address_release(address);
}

static void test_client_connection_list_poll_1() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    ADTList client_connections = list_new();
    list_append(client_connections, client_connection);
    g_assert_cmpint(client_connection_list_poll(client_connections, POLL_TIMEOUT),
                    ==, 0);
    list_release(client_connections);
    connection_release(accepted);
    client_connection_release(client_connection);
    sock_release(server);
    address_release(address);
}

static void test_client_connection_list_poll_2() {
    NETAddress address = address_new("127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETClientConnection client_connection = connect_client_connection(address, 5);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    ADTList client_connections = list_new();
    list_append(client_connections, client_connection);
    connection_push(client_connection->connection,
                    "Sport Club Corinthians Paulista");
    g_assert_cmpint(client_connection_list_poll(client_connections, POLL_TIMEOUT),
                    ==, 1);
    list_release(client_connections);
    connection_release(accepted);
    client_connection_release(client_connection);
    sock_release(server);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/client_connection/connect", test_connect_client_connection_1);
    g_test_add_func("/client_connection/release", test_client_connection_release_1);
    g_test_add_func("/client_connection/get_address",
                    test_client_connection_get_address_1);
    g_test_add_func("/client_connection/set_address",
                    test_client_connection_set_address_1);
    g_test_add_func("/client_connection/get_connection",
                    test_client_connection_get_connection_1);
    g_test_add_func("/client_connection/set_connection",
                    test_client_connection_set_connection_1);
    g_test_add_func("/client_connection/get_expires",
                    test_client_connection_get_expires_1);
    g_test_add_func("/client_connection/set_expires",
                    test_client_connection_set_expires_1);
    g_test_add_func("/client_connection/address_is",
                    test_client_connection_address_is_1);
    g_test_add_func("/client_connection/address_is",
                    test_client_connection_address_is_2);
    g_test_add_func("/client_connection/is_alive",
                    test_client_connection_is_alive_1);
    g_test_add_func("/client_connection/is_alive",
                    test_client_connection_is_alive_2);
    g_test_add_func("/client_connection/is_dead", test_client_connection_is_dead_1);
    g_test_add_func("/client_connection/is_dead", test_client_connection_is_dead_2);
    g_test_add_func("/client_connection/is_on", test_client_connection_is_on_1);
    g_test_add_func("/client_connection/is_on", test_client_connection_is_on_2);
    g_test_add_func("/client_connection/is_off", test_client_connection_is_off_1);
    g_test_add_func("/client_connection/is_off", test_client_connection_is_off_2);
    g_test_add_func("/client_connection/turn_on", test_client_connection_turn_on_1);
    g_test_add_func("/client_connection/turn_off",
                    test_client_connection_turn_off_1);
    g_test_add_func("/client_connection/lasts_for",
                    test_client_connection_lasts_for_1);
    g_test_add_func("/client_connection/out", test_client_connection_out_1);
    g_test_add_func("/client_connection/push", test_client_connection_push_1);
    g_test_add_func("/client_connection/loop", test_client_connection_loop_1);
    g_test_add_func("/client_connection/list_poll",
                    test_client_connection_list_poll_1);
    g_test_add_func("/client_connection/list_poll",
                    test_client_connection_list_poll_2);
    return g_test_run();
}

