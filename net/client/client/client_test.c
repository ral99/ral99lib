#include <glib.h>
#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"

#define CONNECTION_LIFE 300
#define POLL_TIMEOUT 500

static void test_client_new_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(list_size(client->connections), ==, 0);
    g_assert_cmpint(client->connection_life, ==, CONNECTION_LIFE);
    g_assert_cmpint(client->poll_timeout, ==, POLL_TIMEOUT);
    client_release(client);
}

static void test_client_release_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_release(client);
}

static void test_client_get_connections_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_connections(client) == client->connections);
    client_release(client);
}

static void test_client_set_connections_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    List connections = list_new();
    list_full_release(client->connections,
                      (void (*)(void *)) client_connection_release);
    client_set_connections(client, connections);
    g_assert(client->connections == connections);
    client_release(client);
}

static void test_client_get_connection_life_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_connection_life(client) == client->connection_life);
    client_release(client);
}

static void test_client_set_connection_life_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_set_connection_life(client, CONNECTION_LIFE + 1);
    g_assert_cmpint(client->connection_life, ==, CONNECTION_LIFE + 1);
    client_release(client);
}

static void test_client_get_poll_timeout_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert(client_get_poll_timeout(client) == client->poll_timeout);
    client_release(client);
}

static void test_client_set_poll_timeout_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    client_set_poll_timeout(client, POLL_TIMEOUT + 1);
    g_assert_cmpint(client->poll_timeout, ==, POLL_TIMEOUT + 1);
    client_release(client);
}

static void test_client_connection_life_is_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_connection_life_is(client, CONNECTION_LIFE), ==, 1);
    client_release(client);
}

static void test_client_connection_life_is_2() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_connection_life_is(client, CONNECTION_LIFE + 1), ==, 0);
    client_release(client);
}

static void test_client_poll_timeout_is_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_poll_timeout_is(client, POLL_TIMEOUT), ==, 1);
    client_release(client);
}

static void test_client_poll_timeout_is_2() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    g_assert_cmpint(client_poll_timeout_is(client, POLL_TIMEOUT + 1), ==, 0);
    client_release(client);
}

static void test_client_get_connection_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    Address address1 = address_new("127.0.0.1", 5000);
    Address address2 = address_new("127.0.0.1", 5001);
    Address address3 = address_new("127.0.0.1", 5002);
    ClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection3 = connect_client_connection(address3,
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
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    Address address1 = address_new("127.0.0.1", 5000);
    Address address2 = address_new("127.0.0.1", 5001);
    Address address3 = address_new("127.0.0.1", 5002);
    Address address4 = address_new("127.0.0.1", 5003);
    ClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection3 = connect_client_connection(address3,
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
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    Address address1 = address_new("127.0.0.1", 5000);
    Address address2 = address_new("127.0.0.1", 5001);
    Address address3 = address_new("127.0.0.1", 5002);
    ClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    ClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    client_push(client, address1, "Sport Club Corinthians Paulista");
    List out = client_connection_out(client_connection1);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    address_release(address1);
    address_release(address2);
    address_release(address3);
    client_release(client);
}

static void test_client_loop_1() {
    Client client = client_new(CONNECTION_LIFE, POLL_TIMEOUT);
    Sock server = sock_listen(5000);
    Address address1 = address_new("127.0.0.1", 5000);
    Address address2 = address_new("127.0.0.1", 5001);
    Address address3 = address_new("127.0.0.1", 5002);
    ClientConnection client_connection1 = connect_client_connection(address1,
                                                              CONNECTION_LIFE);
    Connection accepted1 = connection_accept(server);
    ClientConnection client_connection2 = connect_client_connection(address2,
                                                              CONNECTION_LIFE);
    Connection accepted2 = connection_accept(server);
    ClientConnection client_connection3 = connect_client_connection(address3,
                                                              CONNECTION_LIFE);
    Connection accepted3 = connection_accept(server);
    client_connection_push(client_connection1, "Sport Club Corinthians Paulista");
    connection_push(accepted2, "Republica Federativa do Brasil");
    list_append(client->connections, client_connection1);
    list_append(client->connections, client_connection2);
    list_append(client->connections, client_connection3);
    for (int i = 0; i < 2; i++) {
        client_loop(client);
        connection_loop(accepted1);
        connection_loop(accepted2);
        connection_loop(accepted3);
    }
    List out1 = client_connection_out(client_connection1);
    List out2 = client_connection_out(client_connection2);
    List out3 = client_connection_out(client_connection3);
    char *text = connection_pop(accepted1);
    g_assert_cmpint(list_size(out1), ==, 0);
    g_assert_cmpint(list_size(out2), ==, 0);
    g_assert_cmpint(list_size(out3), ==, 0);
    g_assert(connection_pop(accepted1) == NULL);
    g_assert(connection_pop(accepted2) == NULL);
    g_assert(connection_pop(accepted3) == NULL);
    g_assert_cmpstr(text, ==, "Sport Club Corinthians Paulista");
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

