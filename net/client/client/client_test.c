#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "net/net.h"
#include "adt/adt.h"

#define CONNECTION_LIFE 300
#define POLL_TIMEOUT 500

static void test_client_new_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(list_size(client->connections), ==, 0);
    g_assert_cmpint(client->connection_life, ==, CONNECTION_LIFE);
    g_assert_cmpint(client->poll_timeout, ==, POLL_TIMEOUT);
    client_release(client);
}

static void test_client_release_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_release(client);
}

static void test_client_get_connections_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_connections(client) == client->connections);
    client_release(client);
}

static void test_client_set_connections_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    ADTList connections = list_new();
    list_full_release(client->connections,
                      (void (*)(void *)) client_connection_release);
    client_set_connections(client, connections);
    g_assert(client->connections == connections);
    client_release(client);
}

static void test_client_get_connection_life_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_connection_life(client) == client->connection_life);
    client_release(client);
}

static void test_client_set_connection_life_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_set_connection_life(client, CONNECTION_LIFE + 1);
    g_assert_cmpint(client->connection_life, ==, CONNECTION_LIFE + 1);
    client_release(client);
}

static void test_client_get_poll_timeout_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_poll_timeout(client) == client->poll_timeout);
    client_release(client);
}

static void test_client_set_poll_timeout_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_set_poll_timeout(client, POLL_TIMEOUT + 1);
    g_assert_cmpint(client->poll_timeout, ==, POLL_TIMEOUT + 1);
    client_release(client);
}

static void test_client_connection_life_is_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_connection_life_is(client, CONNECTION_LIFE), ==, 1);
    client_release(client);
}

static void test_client_connection_life_is_2() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_connection_life_is(client, CONNECTION_LIFE + 1), ==, 0);
    client_release(client);
}

static void test_client_poll_timeout_is_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_poll_timeout_is(client, POLL_TIMEOUT), ==, 1);
    client_release(client);
}

static void test_client_poll_timeout_is_2() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_poll_timeout_is(client, POLL_TIMEOUT + 1), ==, 0);
    client_release(client);
}

static void test_client_get_connection_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    NETAddress address1 = address_new((char *) "127.0.0.1", 5000);
    NETAddress address2 = address_new((char *) "127.0.0.1", 5001);
    NETAddress address3 = address_new((char *) "127.0.0.1", 5002);
    NETClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    g_assert(client_get_connection(client, address1) == client_connection1);
    g_assert(client_get_connection(client, address2) == client_connection2);
    g_assert(client_get_connection(client, address3) == client_connection3);
    address_release(address1);
    address_release(address2);
    address_release(address3);
    client_release(client);
}

static void test_client_get_or_create_connection_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    NETAddress address1 = address_new((char *) "127.0.0.1", 5000);
    NETAddress address2 = address_new((char *) "127.0.0.1", 5001);
    NETAddress address3 = address_new((char *) "127.0.0.1", 5002);
    NETAddress address4 = address_new((char *) "127.0.0.1", 5003);
    NETClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    client_get_or_create_connection(client, address4);
    g_assert_cmpint(list_size(client->connections), ==, 4);
    address_release(address1);
    address_release(address2);
    address_release(address3);
    address_release(address4);
    client_release(client);
}

static void test_client_push_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    NETAddress address1 = address_new((char *) "127.0.0.1", 5000);
    NETAddress address2 = address_new((char *) "127.0.0.1", 5001);
    NETAddress address3 = address_new((char *) "127.0.0.1", 5002);
    NETClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    NETClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    client_push(client, address1, (char *) "Sport Club Corinthians Paulista");
    ADTList out = client_connection_out(client_connection1);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr((char *) list_at(out, 0), ==, (char *) "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    address_release(address1);
    address_release(address2);
    address_release(address3);
    client_release(client);
}

static void test_client_loop_1() {
    NETClient client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETAddress address1 = address_new((char *) "127.0.0.1", 5000);
    NETAddress address2 = address_new((char *) "127.0.0.1", 5001);
    NETAddress address3 = address_new((char *) "127.0.0.1", 5002);
    NETClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    sleep(1);
    NETConnection accepted1 = connection_accept(server);
    NETClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    sleep(1);
    NETConnection accepted2 = connection_accept(server);
    NETClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    sleep(1);
    NETConnection accepted3 = connection_accept(server);
    client_connection_push(client_connection1, (char *) "Sport Club Corinthians Paulista");
    connection_push(accepted2, (char *) "Republica Federativa do Brasil");
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    for (int i = 0; i < 2; i++) {
        client_loop(client);
        connection_loop(accepted1);
        connection_loop(accepted2);
        connection_loop(accepted3);
        sleep(1);
    }
    ADTList out1 = client_connection_out(client_connection1);
    ADTList out2 = client_connection_out(client_connection2);
    ADTList out3 = client_connection_out(client_connection3);
    char *text = connection_pop(accepted1);
    g_assert_cmpint(list_size(out1), ==, 0);
    g_assert_cmpint(list_size(out2), ==, 0);
    g_assert_cmpint(list_size(out3), ==, 0);
    g_assert(connection_pop(accepted1) == NULL);
    g_assert(connection_pop(accepted2) == NULL);
    g_assert(connection_pop(accepted3) == NULL);
    g_assert_cmpstr(text, ==, (char *) "Sport Club Corinthians Paulista");
    free(text);
    list_full_release(out1, free);
    list_full_release(out2, free);
    list_full_release(out3, free);
    address_release(address1);
    address_release(address2);
    address_release(address3);
    connection_release(accepted1);
    connection_release(accepted2);
    connection_release(accepted3);
    client_release(client);
    sock_release(server);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/client/new", test_client_new_1);
    g_test_add_func("/client/release", test_client_release_1);
    g_test_add_func("/client/get_connections", test_client_get_connections_1);
    g_test_add_func("/client/set_connections", test_client_set_connections_1);
    g_test_add_func("/client/get_connection_life",
                    test_client_get_connection_life_1);
    g_test_add_func("/client/set_connection_life",
                    test_client_set_connection_life_1);
    g_test_add_func("/client/get_poll_timeout", test_client_get_poll_timeout_1);
    g_test_add_func("/client/set_poll_timeout", test_client_set_poll_timeout_1);
    g_test_add_func("/client/connection_life_is", test_client_connection_life_is_1);
    g_test_add_func("/client/connection_life_is", test_client_connection_life_is_2);
    g_test_add_func("/client/poll_timeout_is", test_client_poll_timeout_is_1);
    g_test_add_func("/client/poll_timeout_is", test_client_poll_timeout_is_2);
    g_test_add_func("/client/get_connection", test_client_get_connection_1);
    g_test_add_func("/client/get_or_create_connection",
                    test_client_get_or_create_connection_1);
    g_test_add_func("/client/push", test_client_push_1);
    g_test_add_func("/client/loop", test_client_loop_1);
    return g_test_run();
}

