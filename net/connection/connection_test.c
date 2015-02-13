#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "net/net.h"
#include "adt/adt.h"
#include "str/str.h"

#define POLL_TIMEOUT 500

static void test_connection_connect_accept_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETConnection connected = connection_connect(address);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    g_assert_cmpint(sock_is_on(connected->sock), ==, 1);
    g_assert_cmpint(list_size(connected->in), ==, 0);
    g_assert_cmpint(list_size(connected->out), ==, 0);
    g_assert_cmpint(sock_is_on(accepted->sock), ==, 1);
    g_assert_cmpint(list_size(accepted->in), ==, 0);
    g_assert_cmpint(list_size(accepted->out), ==, 0);
    connection_release(accepted);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_connection_release_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connected = connection_connect(address);
    connection_release(connected);
    address_release(address);
}

static void test_connection_get_sock_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    g_assert(connection_get_sock(connection) == connection->sock);
    connection_release(connection);
    address_release(address);
}

static void test_connection_set_sock_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    NETSock sock = sock_new(0, 1);
    sock_release(connection->sock);
    connection_set_sock(connection, sock);
    g_assert(connection->sock == sock);
    connection_release(connection);
    address_release(address);
}

static void test_connection_get_in_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    g_assert(connection_get_in(connection) == connection->in);
    connection_release(connection);
    address_release(address);
}

static void test_connection_set_in_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    ADTList in = list_new();
    list_release(connection->in);
    connection_set_in(connection, in);
    g_assert(connection->in == in); 
    connection_release(connection);
    address_release(address);
}

static void test_connection_get_out_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    g_assert(connection_get_out(connection) == connection->out);
    connection_release(connection);
    address_release(address);
}

static void test_connection_set_out_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    ADTList out = list_new();
    list_release(connection->out);
    connection_set_out(connection, out);
    g_assert(connection->out == out); 
    connection_release(connection);
    address_release(address);
}

static void test_connection_is_on_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    g_assert_cmpint(connection_is_on(connection), ==, 1);
    connection_release(connection);
    address_release(address);
}

static void test_connection_is_on_2() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    sock_turn_off(connection->sock);
    g_assert_cmpint(connection_is_on(connection), ==, 0);
    connection_release(connection);
    address_release(address);
}

static void test_connection_is_off_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    g_assert_cmpint(connection_is_off(connection), ==, 0);
    connection_release(connection);
    address_release(address);
}

static void test_connection_is_off_2() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    sock_turn_off(connection->sock);
    g_assert_cmpint(connection_is_off(connection), ==, 1);
    connection_release(connection);
    address_release(address);
}

static void test_connection_turn_off_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    connection_turn_off(connection);
    g_assert_cmpint(sock_is_off(connection->sock), ==, 1);
    connection_release(connection);
    address_release(address);
}

static void test_connection_out_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    list_append(connection->out, str_dup((char *) "Sport"));
    list_append(connection->out, str_dup((char *) "Club"));
    list_append(connection->out, str_dup((char *) "Corinthians"));
    list_append(connection->out, str_dup((char *) "Paulista"));
    ADTList out = connection_out(connection);
    g_assert_cmpint(list_equals_cmp(connection->out, out,
                    (int (*)(void *, void *)) str_equals), ==, 1);
    list_full_release(out, free);
    connection_release(connection);
    address_release(address);
}

static void test_connection_push_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    connection_push(connection, (char *) "Sport");
    connection_push(connection, (char *) "Club");
    connection_push(connection, (char *) "Corinthians");
    connection_push(connection, (char *) "Paulista");
    ADTList out = list_new();
    list_append(out, (char *) "Sport");
    list_append(out, (char *) "Club");
    list_append(out, (char *) "Corinthians");
    list_append(out, (char *) "Paulista");
    g_assert_cmpint(list_equals_cmp(connection->out, out,
                                    (int (*)(void *, void *)) str_equals), ==, 1);
    list_release(out);
    connection_release(connection);
    address_release(address);
}

static void test_connection_pop_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETConnection connection = connection_connect(address);
    list_append(connection->in, str_dup((char *) "Sport"));
    list_append(connection->in, str_dup((char *) "Club"));
    list_append(connection->in, str_dup((char *) "Corinthians"));
    list_append(connection->in, str_dup((char *) "Paulista"));
    char *text = connection_pop(connection);
    ADTList in = list_new();
    list_append(in, (char *) "Club");
    list_append(in, (char *) "Corinthians");
    list_append(in, (char *) "Paulista");
    g_assert_cmpstr(text, ==, (char *) "Sport");
    g_assert_cmpint(list_equals_cmp(connection->in, in,
                                    (int (*)(void *, void *)) str_equals), ==, 1);
    free(text);
    list_release(in);
    connection_release(connection);
    address_release(address);
}

static void test_connection_send_recv_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETConnection connected = connection_connect(address);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    list_append(connected->out, str_dup((char *) "Sport Club Corinthians Paulista"));
    connection_send(connected);
    sleep(1);
    connection_recv(accepted);
    sleep(1);
    g_assert_cmpint(list_size(connected->out), ==, 0);
    g_assert_cmpint(list_size(accepted->in), ==, 1);
    g_assert_cmpstr((char *) list_at(accepted->in, 0), ==,
                    (char *) "Sport Club Corinthians Paulista");
    connection_release(accepted);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_connection_loop_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETConnection connected = connection_connect(address);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    list_append(connected->out, str_dup((char *) "Sport Club Corinthians Paulista"));
    connection_loop(connected);
    sleep(1);
    connection_loop(accepted);
    sleep(1);
    g_assert_cmpint(list_size(connected->out), ==, 0);
    g_assert_cmpint(list_size(accepted->in), ==, 1);
    g_assert_cmpstr((char *) list_at(accepted->in, 0), ==,
                    (char *) "Sport Club Corinthians Paulista");
    connection_release(accepted);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_connection_list_poll_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETConnection connected = connection_connect(address);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    ADTList connections = list_new();
    list_append(connections, connected);
    list_append(connections, accepted);
    g_assert_cmpint(connection_list_poll(connections, POLL_TIMEOUT), ==, 0);
    list_release(connections);
    connection_release(accepted);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_connection_list_poll_2() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETConnection connected = connection_connect(address);
    sleep(1);
    NETConnection accepted = connection_accept(server);
    sleep(1);
    ADTList connections = list_new();
    list_append(connections, connected);
    list_append(connections, accepted);
    list_append(connected->out, str_dup((char *) "Sport Club Corinthians Paulista"));
    g_assert_cmpint(connection_list_poll(connections, POLL_TIMEOUT), ==, 1);
    list_release(connections);
    connection_release(accepted);
    connection_release(connected);
    sock_release(server);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/connection/connect_accept", test_connection_connect_accept_1);
    g_test_add_func("/connection/release", test_connection_release_1);
    g_test_add_func("/connection/get_sock", test_connection_get_sock_1);
    g_test_add_func("/connection/set_sock", test_connection_set_sock_1);
    g_test_add_func("/connection/get_in", test_connection_get_in_1);
    g_test_add_func("/connection/set_in", test_connection_set_in_1);
    g_test_add_func("/connection/get_out", test_connection_get_out_1);
    g_test_add_func("/connection/set_out", test_connection_set_out_1);
    g_test_add_func("/connection/is_on", test_connection_is_on_1);
    g_test_add_func("/connection/is_on", test_connection_is_on_2);
    g_test_add_func("/connection/is_off", test_connection_is_off_1);
    g_test_add_func("/connection/is_off", test_connection_is_off_2);
    g_test_add_func("/connection/turn_off", test_connection_turn_off_1);
    g_test_add_func("/connection/out", test_connection_out_1);
    g_test_add_func("/connection/push", test_connection_push_1);
    g_test_add_func("/connection/pop", test_connection_pop_1);
    g_test_add_func("/connection/send_recv", test_connection_send_recv_1);
    g_test_add_func("/connection/loop", test_connection_loop_1);
    g_test_add_func("/connection/list_poll", test_connection_list_poll_1);
    g_test_add_func("/connection/list_poll", test_connection_list_poll_2);
    return g_test_run();
}

