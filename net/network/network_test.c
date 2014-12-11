#include <glib.h>
#include <stdlib.h>

#include "net/network/network.h"
#include "net/client/client.h"
#include "net/server/server.h"
#include "net/address/address.h"
#include "net/connection/connection.h"
#include "net/message/message.h"
#include "adt/adt.h"

#define CONNECTION_LIFE 300
#define CLIENT_POLL_TIMEOUT 500
#define SERVER_POLL_TIMEOUT 500

static void test_network_new_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert(network->client != NULL);
    g_assert(network->server != NULL);
    g_assert_cmpint(client_connection_life_is(network->client, CONNECTION_LIFE), ==,
                    1);
    g_assert_cmpint(client_poll_timeout_is(network->client, CLIENT_POLL_TIMEOUT), ==,
                    1);
    g_assert_cmpint(server_poll_timeout_is(network->server, SERVER_POLL_TIMEOUT), ==,
                    1);
    g_assert_cmpint(server_port_is(network->server, 5000), ==, 1);
    network_release(network);
}

static void test_network_release_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    network_release(network);
}

static void test_network_get_client_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert(network_get_client(network) == network->client);
    network_release(network);
}

static void test_network_set_client_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    Client client = client_new(CONNECTION_LIFE, CLIENT_POLL_TIMEOUT);
    client_release(network->client);
    network_set_client(network, client);
    g_assert(network->client == client);
    network_release(network);
}

static void test_network_get_server_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert(network_get_server(network) == network->server);
    network_release(network);
}

static void test_network_set_server_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    Server server = server_listen(5001, SERVER_POLL_TIMEOUT);
    server_release(network->server);
    network_set_server(network, server);
    g_assert(network->server == server);
    network_release(network);
}

static void test_network_port_is_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_port_is(network, 5000), ==, 1);
    network_release(network);
}

static void test_network_port_is_2() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_port_is(network, 5001), ==, 0);
    network_release(network);
}

static void test_network_connection_life_is_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_connection_life_is(network, CONNECTION_LIFE), ==, 1);
    network_release(network);
}

static void test_network_connection_life_is_2() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_connection_life_is(network, CONNECTION_LIFE + 1), ==, 0);
    network_release(network);
}

static void test_network_client_poll_timeout_is_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_client_poll_timeout_is(network, CLIENT_POLL_TIMEOUT), ==,
                    1);
    network_release(network);
}

static void test_network_client_poll_timeout_is_2() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_client_poll_timeout_is(network, CLIENT_POLL_TIMEOUT + 1),
                    ==, 0);
    network_release(network);
}

static void test_network_server_poll_timeout_is_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_server_poll_timeout_is(network, SERVER_POLL_TIMEOUT), ==,
                    1);
    network_release(network);
}

static void test_network_server_poll_timeout_is_2() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    g_assert_cmpint(network_server_poll_timeout_is(network, SERVER_POLL_TIMEOUT + 1),
                    ==, 0);
    network_release(network);
}

static void test_network_reply_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    Address address = address_new("127.0.0.1", 5000);
    Connection connection = connection_connect(address);
    connection_push(connection, "Sport Club Corinthians Paulista");
    for (int i = 0; i < 2; i++) {
        server_loop(network->server);
        connection_loop(connection);
    }
    Message message = server_pop(network->server);
    char *id = message_id(message);
    network_reply(network, id, "Republica Federativa do Brasil");
    for (int i = 0; i < 2; i++) {
        server_loop(network->server);
        connection_loop(connection);
    }
    char *text = connection_pop(connection);
    g_assert_cmpstr(text, ==, "Republica Federativa do Brasil");
    free(text);
    free(id);
    message_release(message);
    connection_release(connection);
    address_release(address);
    network_release(network);
}

static void test_network_send_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    Address address = address_new("127.0.0.1", 5000);
    network_send(network, address, "Sport Club Corinthians Paulista");
    List out = client_connection_out(client_get_connection(network->client,
                                                           address));
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    address_release(address);
    network_release(network);
}

static void test_network_recv_1() {
    Network network = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                  SERVER_POLL_TIMEOUT);
    Address address = address_new("127.0.0.1", 5000);
    Connection connection = connection_connect(address);
    connection_push(connection, "Sport Club Corinthians Paulista");
    for (int i = 0; i < 2; i++) {
        server_loop(network->server);
        connection_loop(connection);
    }
    Message message = network_recv(network);
    char *text = message_text(message);
    g_assert_cmpstr(text, ==, "Sport Club Corinthians Paulista");
    free(text);
    message_release(message);
    connection_release(connection);
    address_release(address);
    network_release(network);
}

static void test_network_loop_1() {
    Network network1 = network_new(5000, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                   SERVER_POLL_TIMEOUT);
    Network network2 = network_new(5001, CONNECTION_LIFE, CLIENT_POLL_TIMEOUT,
                                   SERVER_POLL_TIMEOUT);
    Address address1 = address_new("127.0.0.1", 5000);
    Address address2 = address_new("127.0.0.1", 5001);
    client_push(network1->client, address2, "Sport Club Corinthians Paulista");
    client_push(network2->client, address1, "Republica Federativa do Brasil");
    for (int i = 0; i < 2; i++) {
        network_loop(network1);
        network_loop(network2);
    }
    Message message1 = server_pop(network1->server);
    Message message2 = server_pop(network2->server);
    char *text1 = message_text(message1);
    char *text2 = message_text(message2);
    g_assert_cmpstr(text1, ==, "Republica Federativa do Brasil");
    g_assert_cmpstr(text2, ==, "Sport Club Corinthians Paulista");
    free(text1);
    free(text2);
    message_release(message1);
    message_release(message2);
    address_release(address1);
    address_release(address2);
    network_release(network1);
    network_release(network2);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/network/new", test_network_new_1);
    g_test_add_func("/network/release", test_network_release_1);
    g_test_add_func("/network/get_client", test_network_get_client_1);
    g_test_add_func("/network/set_client", test_network_set_client_1);
    g_test_add_func("/network/get_server", test_network_get_server_1);
    g_test_add_func("/network/set_server", test_network_set_server_1);
    g_test_add_func("/network/port_is", test_network_port_is_1);
    g_test_add_func("/network/port_is", test_network_port_is_2);
    g_test_add_func("/network/connection_life_is",
                    test_network_connection_life_is_1);
    g_test_add_func("/network/connection_life_is",
                    test_network_connection_life_is_2);
    g_test_add_func("/network/client_poll_timeout_is",
                    test_network_client_poll_timeout_is_1);
    g_test_add_func("/network/client_poll_timeout_is",
                    test_network_client_poll_timeout_is_2);
    g_test_add_func("/network/server_poll_timeout_is",
                    test_network_server_poll_timeout_is_1);
    g_test_add_func("/network/server_poll_timeout_is",
                    test_network_server_poll_timeout_is_2);
    g_test_add_func("/network/reply", test_network_reply_1);
    g_test_add_func("/network/send", test_network_send_1);
    g_test_add_func("/network/recv", test_network_recv_1);
    g_test_add_func("/network/loop", test_network_loop_1);
    return g_test_run();
}

