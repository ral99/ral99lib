#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "net/net.h"
#include "adt/adt.h"

#define POLL_TIMEOUT 500

static void test_server_listen_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server->port, ==, 5000);
    g_assert_cmpint(server->poll_timeout, ==, POLL_TIMEOUT);
    g_assert_cmpint(sock_is_on(server->sock), ==, 1);
    g_assert_cmpint(list_size(server->connections), ==, 0);
    g_assert_cmpint(list_size(server->messages), ==, 0);
    server_release(server);
}

static void test_server_release_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    server_release(server);
}

static void test_server_get_port_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_get_port(server), ==, server->port);
    server_release(server);
}

static void test_server_set_port_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    server_set_port(server, 5001);
    g_assert_cmpint(server->port, ==, 5001);
    server_release(server);
}

static void test_server_get_poll_timeout_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_get_poll_timeout(server), ==, server->poll_timeout);
    server_release(server);
}

static void test_server_set_poll_timeout_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    server_set_poll_timeout(server, POLL_TIMEOUT + 1);
    g_assert_cmpint(server->poll_timeout, ==, POLL_TIMEOUT + 1);
    server_release(server);
}

static void test_server_get_sock_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert(server_get_sock(server) == server->sock);
    server_release(server);
}

static void test_server_set_sock_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    Sock sock = sock_new(0, 1);
    sock_release(server->sock);
    server_set_sock(server, sock);
    g_assert(server->sock == sock);
    server_release(server);
}

static void test_server_get_connections_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert(server_get_connections(server) == server->connections);
    server_release(server);
}

static void test_server_set_connections_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    List connections = list_new();
    list_release(server->connections);
    server_set_connections(server, connections);
    g_assert(server->connections == connections);
    server_release(server);
}

static void test_server_get_messages_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert(server_get_messages(server) == server->messages);
    server_release(server);
}

static void test_server_set_messages_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    List messages = list_new();
    list_release(server->messages);
    server_set_messages(server, messages);
    g_assert(server->messages == messages);
    server_release(server);
}

static void test_server_port_is_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_port_is(server, 5000), ==, 1);
    server_release(server);
}

static void test_server_port_is_2() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_port_is(server, 5001), ==, 0);
    server_release(server);
}

static void test_server_poll_timeout_is_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_poll_timeout_is(server, POLL_TIMEOUT), ==, 1);
    server_release(server);
}

static void test_server_poll_timeout_is_2() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    g_assert_cmpint(server_poll_timeout_is(server, POLL_TIMEOUT + 1), ==, 0);
    server_release(server);
}

static void test_server_accept_1() {
    Address address = address_new("127.0.0.1", 5000);
    Server server = server_listen(5000, POLL_TIMEOUT);
    sleep(1);
    Connection connected = connection_connect(address);
    sleep(1);
    server_accept(server);
    g_assert_cmpint(list_size(server->connections), ==, 1);
    connection_release(connected);
    server_release(server);
    address_release(address);
}

static void test_server_push_1() {
    Address address = address_new("127.0.0.1", 5000);
    Server server = server_listen(5000, POLL_TIMEOUT);
    sleep(1);
    Connection connected = connection_connect(address);
    sleep(1);
    ServerConnection accepted = accept_server_connection(server->sock);
    char *id = server_connection_id(accepted);
    list_append(server->connections, accepted);
    server_push(server, id, "Sport Club Corinthians Paulista");
    List out = server_connection_out(accepted);
    g_assert_cmpint(list_size(out), ==, 1);
    g_assert_cmpstr(list_at(out, 0), ==, "Sport Club Corinthians Paulista");
    list_full_release(out, free);
    free(id);
    connection_release(connected);
    server_release(server);
    address_release(address);
}

static void test_server_pop_1() {
    Server server = server_listen(5000, POLL_TIMEOUT);
    Message message = message_new("abc", "Sport Club Corinthians Paulista");
    list_append(server->messages, message);
    g_assert(server_pop(server) == message);
    g_assert(server_pop(server) == NULL);
    message_release(message);
    server_release(server);
}

static void test_server_loop_1() {
    Address address = address_new("127.0.0.1", 5000);
    Server server = server_listen(5000, POLL_TIMEOUT);
    sleep(1);
    Connection connected1 = connection_connect(address);
    sleep(1);
    ServerConnection accepted1 = accept_server_connection(server->sock);
    sleep(1);
    Connection connected2 = connection_connect(address);
    sleep(1);
    ServerConnection accepted2 = accept_server_connection(server->sock);
    sleep(1);
    Connection connected3 = connection_connect(address);
    sleep(1);
    server_loop(server);
    sleep(1);
    list_append(server->connections, accepted1);
    list_append(server->connections, accepted2);
    g_assert_cmpint(list_size(server->connections), ==, 3);
    server_connection_push(accepted1, "Sport Club Corinthians Paulista");
    server_connection_push(accepted2, "Republica Federativa do Brasil");
    connection_push(connected2, "Sport Club Corinthians Paulista");
    connection_push(connected3, "Republica Federativa do Brasil");
    connection_turn_off(connected1);
    for (int i = 0; i < 2; i++) {
        connection_loop(connected1);
        connection_loop(connected2);
        connection_loop(connected3);
        server_loop(server);
        sleep(1);
    }
    char *text = connection_pop(connected2);
    g_assert_cmpint(list_size(server->connections), ==, 2);
    g_assert_cmpint(list_size(server->messages), ==, 2);
    g_assert_cmpstr(text, ==, "Republica Federativa do Brasil");
    free(text);
    connection_release(connected1);
    connection_release(connected2);
    connection_release(connected3);
    server_release(server);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/server/listen", test_server_listen_1);
    g_test_add_func("/server/release", test_server_release_1);
    g_test_add_func("/server/get_port", test_server_get_port_1);
    g_test_add_func("/server/set_port", test_server_set_port_1);
    g_test_add_func("/server/get_poll_timeout", test_server_get_poll_timeout_1);
    g_test_add_func("/server/set_poll_timeout", test_server_set_poll_timeout_1);
    g_test_add_func("/server/get_sock", test_server_get_sock_1);
    g_test_add_func("/server/set_sock", test_server_set_sock_1);
    g_test_add_func("/server/get_connections", test_server_get_connections_1);
    g_test_add_func("/server/set_connections", test_server_set_connections_1);
    g_test_add_func("/server/get_messages", test_server_get_messages_1);
    g_test_add_func("/server/set_messages", test_server_set_messages_1);
    g_test_add_func("/server/port_is", test_server_port_is_1);
    g_test_add_func("/server/port_is", test_server_port_is_2);
    g_test_add_func("/server/poll_timeout_is", test_server_poll_timeout_is_1);
    g_test_add_func("/server/poll_timeout_is", test_server_poll_timeout_is_2);
    g_test_add_func("/server/accept", test_server_accept_1);
    g_test_add_func("/server/push", test_server_push_1);
    g_test_add_func("/server/pop", test_server_pop_1);
    g_test_add_func("/server/loop", test_server_loop_1);
    return g_test_run();
}

