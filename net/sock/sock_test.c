#include <fcntl.h>
#include <glib.h>
#include <stdlib.h>
#include <unistd.h>

#include "net/net.h"
#include "mem/mem.h"

#define POLL_TIMEOUT 500

static void test_sock_new_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock->fd, ==, 0);
    g_assert_cmpint(sock->on, ==, 1);
    sock_release(sock);
}

static void test_sock_nonblocking_1() {
    NETSock sock = sock_nonblocking(-1);
    g_assert_cmpint(sock->fd, ==, -1);
    g_assert_cmpint(sock->on, ==, 0);
    sock_release(sock);
}

static void test_sock_nonblocking_2() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    NETSock sock = sock_nonblocking(fd);
    g_assert_cmpint(sock->fd, ==, fd);
    g_assert_cmpint(sock->on, ==, 1);
    g_assert_cmpint(fcntl(sock->fd, F_GETFL) & O_NONBLOCK, >, 0);
    sock_release(sock);
}

static void test_sock_listen_accept_connect_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    NETSock accepted = sock_accept(server);
    sleep(1);
    g_assert_cmpint(server->fd, >=, 0);
    g_assert_cmpint(server->on, ==, 1);
    g_assert_cmpint(fcntl(server->fd, F_GETFL) & O_NONBLOCK, >, 0);
    g_assert_cmpint(connected->fd, >=, 0);
    g_assert_cmpint(connected->on, ==, 1);
    g_assert_cmpint(fcntl(connected->fd, F_GETFL) & O_NONBLOCK, >, 0);
    g_assert_cmpint(accepted->fd, >=, 0);
    g_assert_cmpint(accepted->on, ==, 1);
    g_assert_cmpint(fcntl(accepted->fd, F_GETFL) & O_NONBLOCK, >, 0);
    sock_release(accepted);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_release_1() {
    NETSock sock = sock_new(0, 1);
    sock_release(sock);
}

static void test_sock_get_fd_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_get_fd(sock), ==, sock->fd);
    sock_release(sock);
}

static void test_sock_set_fd_1() {
    NETSock sock = sock_new(0, 1);
    sock_set_fd(sock, 1);
    g_assert_cmpint(sock->fd, ==, 1);
    sock_release(sock);
}

static void test_sock_get_on_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_get_on(sock), ==, sock->on);
    sock_release(sock);
}

static void test_sock_set_on_1() {
    NETSock sock = sock_new(0, 1);
    sock_set_on(sock, 0);
    g_assert_cmpint(sock->on, ==, 0);
    sock_release(sock);
}

static void test_sock_fd_is_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_fd_is(sock, 0), ==, 1);
    sock_release(sock);
}

static void test_sock_fd_is_2() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_fd_is(sock, 1), ==, 0);
    sock_release(sock);
}

static void test_sock_is_on_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_is_on(sock), ==, 1);
    sock_release(sock);
}

static void test_sock_is_on_2() {
    NETSock sock = sock_new(0, 0);
    g_assert_cmpint(sock_is_on(sock), ==, 0);
    sock_release(sock);
}

static void test_sock_is_off_1() {
    NETSock sock = sock_new(0, 1);
    g_assert_cmpint(sock_is_off(sock), ==, 0);
    sock_release(sock);
}

static void test_sock_is_off_2() {
    NETSock sock = sock_new(0, 0);
    g_assert_cmpint(sock_is_off(sock), ==, 1);
    sock_release(sock);
}

static void test_sock_turn_off_1() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    NETSock sock = sock_nonblocking(fd);
    sock_turn_off(sock);
    g_assert_cmpint(sock->fd, ==, -1);
    g_assert_cmpint(sock->on, ==, 0);
    sock_release(sock);
}

static void test_sock_turn_off_2() {
    NETSock sock = sock_nonblocking(-1);
    sock_turn_off(sock);
    g_assert_cmpint(sock->fd, ==, -1);
    g_assert_cmpint(sock->on, ==, 0);
    sock_release(sock);
}

static void test_sock_send_recv_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    NETSock accepted = sock_accept(server);
    sleep(1);
    sock_send(connected, (char *) "Sport Club Corinthians Paulista");
    sleep(1);
    char *text = sock_recv(accepted);
    g_assert_cmpstr(text, ==, (char *) "Sport Club Corinthians Paulista");
    free(text);
    sock_release(accepted);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_list_poll_1() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    int nfds = 2;
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    socks[0] = server;
    socks[1] = connected;
    pollin[0] = pollout[0] = 0;
    pollin[1] = pollout[1] = 0;
    g_assert_cmpint(sock_list_poll(socks, pollin, pollout, nfds, POLL_TIMEOUT), ==,
                    0);
    free(socks);
    free(pollin);
    free(pollout);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_list_poll_2() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    int nfds = 2;
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    socks[0] = server;
    socks[0] = server;
    socks[1] = connected;
    pollin[0] = pollout[0] = 1;
    pollin[1] = pollout[1] = 1;
    g_assert_cmpint(sock_list_poll(socks, pollin, pollout, nfds, POLL_TIMEOUT), ==,
                    2);
    free(socks);
    free(pollin);
    free(pollout);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_list_poll_3() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    NETSock accepted = sock_accept(server);
    sleep(1);
    int nfds = 3;
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    socks[0] = server;
    socks[1] = connected;
    socks[2] = accepted;
    pollin[0] = pollout[0] = 0;
    pollin[1] = pollout[1] = 1;
    pollin[2] = pollout[2] = 1;
    g_assert_cmpint(sock_list_poll(socks, pollin, pollout, nfds, POLL_TIMEOUT), ==,
                    2);
    free(socks);
    free(pollin);
    free(pollout);
    sock_release(accepted);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_list_poll_4() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    NETSock accepted = sock_accept(server);
    sleep(1);
    int nfds = 3;
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    socks[0] = server;
    socks[1] = connected;
    socks[2] = accepted;
    pollin[0] = pollout[0] = 1;
    pollin[1] = pollout[1] = 1;
    pollin[2] = pollout[2] = 1;
    g_assert_cmpint(sock_list_poll(socks, pollin, pollout, nfds, POLL_TIMEOUT), ==,
                    2);
    free(socks);
    free(pollin);
    free(pollout);
    sock_release(accepted);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

static void test_sock_list_poll_5() {
    NETAddress address = address_new((char *) "127.0.0.1", 5000);
    NETSock server = sock_listen(5000);
    sleep(1);
    NETSock connected = sock_connect(address);
    sleep(1);
    NETSock accepted = sock_accept(server);
    sleep(1);
    int nfds = 3;
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    socks[0] = server;
    socks[1] = connected;
    socks[2] = accepted;
    pollin[0] = pollin[1] = pollin[2] = 1;
    pollout[0] = pollout[1] = pollout[2] = 0;
    g_assert_cmpint(sock_list_poll(socks, pollin, pollout, nfds, POLL_TIMEOUT), ==,
                    0);
    free(socks);
    free(pollin);
    free(pollout);
    sock_release(accepted);
    sock_release(connected);
    sock_release(server);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/sock/new", test_sock_new_1);
    g_test_add_func("/sock/nonblocking", test_sock_nonblocking_1);
    g_test_add_func("/sock/nonblocking", test_sock_nonblocking_2);
    g_test_add_func("/sock/listen_accept_connect",
                    test_sock_listen_accept_connect_1);
    g_test_add_func("/sock/release", test_sock_release_1);
    g_test_add_func("/sock/get_fd", test_sock_get_fd_1);
    g_test_add_func("/sock/set_fd", test_sock_set_fd_1);
    g_test_add_func("/sock/get_on", test_sock_get_on_1);
    g_test_add_func("/sock/set_on", test_sock_set_on_1);
    g_test_add_func("/sock/fd_is", test_sock_fd_is_1);
    g_test_add_func("/sock/fd_is", test_sock_fd_is_2);
    g_test_add_func("/sock/is_on", test_sock_is_on_1);
    g_test_add_func("/sock/is_on", test_sock_is_on_2);
    g_test_add_func("/sock/is_off", test_sock_is_off_1);
    g_test_add_func("/sock/is_off", test_sock_is_off_2);
    g_test_add_func("/sock/turn_off", test_sock_turn_off_1);
    g_test_add_func("/sock/turn_off", test_sock_turn_off_2);
    g_test_add_func("/sock/send_recv", test_sock_send_recv_1);
    g_test_add_func("/sock/list_poll", test_sock_list_poll_1);
    g_test_add_func("/sock/list_poll", test_sock_list_poll_2);
    g_test_add_func("/sock/list_poll", test_sock_list_poll_3);
    g_test_add_func("/sock/list_poll", test_sock_list_poll_4);
    g_test_add_func("/sock/list_poll", test_sock_list_poll_5);
    return g_test_run();
}

