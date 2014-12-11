#include <stdlib.h>

#include "net/connection/connection.h"
#include "net/address/address.h"
#include "net/sock/sock.h"
#include "util/util.h"
#include "adt/adt.h"

Connection connection_connect(Address address) {
    Connection connection = memalloc(sizeof(*connection));
    connection->in = list_new();
    connection->out = list_new();
    connection->sock = sock_connect(address);
    return connection;
}

Connection connection_accept(Sock server_sock) {
    Connection connection = memalloc(sizeof(*connection));
    connection->in = list_new();
    connection->out = list_new();
    connection->sock = sock_accept(server_sock);
    return connection;
}

void connection_release(Connection connection) {
    sock_release(connection->sock);
    list_full_release(connection->in, free);
    list_full_release(connection->out, free);
    free(connection);
}

Sock connection_get_sock(Connection connection) {
    return connection->sock;
}

void connection_set_sock(Connection connection, Sock sock) {
    connection->sock = sock;
}

List connection_get_in(Connection connection) {
    return connection->in;
}

void connection_set_in(Connection connection, List in) {
    connection->in = in;
}

List connection_get_out(Connection connection) {
    return connection->out;
}

void connection_set_out(Connection connection, List out) {
    connection->out = out;
}

int connection_is_on(Connection connection) {
    return sock_is_on(connection->sock);
}

int connection_is_off(Connection connection) {
    return sock_is_off(connection->sock);
}

void connection_turn_off(Connection connection) {
    sock_turn_off(connection->sock);
}

List connection_out(Connection connection) {
    return list_map(connection->out, (void *(*)(void *)) str_dup);
}

void connection_push(Connection connection, char *text) {
    list_append(connection->out, str_dup(text));
}

char *connection_pop(Connection connection) {
    return list_pop_front(connection->in);
}

void connection_send(Connection connection) {
    char *text = list_at(connection->out, 0);
    if (text && sock_send(connection->sock, text))
        list_full_remove_at(connection->out, 0, free);
}

void connection_recv(Connection connection) {
    char *text = sock_recv(connection->sock);
    if (text)
        list_append(connection->in, text);
}

void connection_loop(Connection connection) {
    if (sock_is_on(connection->sock)) {
        connection_send(connection);
        connection_recv(connection);
    }
}

int connection_list_poll(List connections, int timeout) {
    int nfds = list_size(connections);
    int pollin[nfds], pollout[nfds];
    Sock socks[nfds];
    for (int i = 0; i < nfds; i++) {
        Connection connection = list_at(connections, i);
        socks[i] = connection->sock;
        pollin[i] = 1;
        pollout[i] = (list_head(connection->out)) ? 1 : 0;
    }
    return sock_list_poll(socks, pollin, pollout, nfds, timeout);
}

