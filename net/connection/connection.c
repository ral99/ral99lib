#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "str/str.h"

NETConnection connection_connect(NETAddress address) {
    NETConnection connection = (NETConnection) memalloc(sizeof(*connection));
    connection->in = list_new();
    connection->out = list_new();
    connection->sock = sock_connect(address);
    return connection;
}

NETConnection connection_accept(NETSock server_sock) {
    NETConnection connection = (NETConnection) memalloc(sizeof(*connection));
    connection->in = list_new();
    connection->out = list_new();
    connection->sock = sock_accept(server_sock);
    return connection;
}

void connection_release(NETConnection connection) {
    sock_release(connection->sock);
    list_full_release(connection->in, free);
    list_full_release(connection->out, free);
    free(connection);
}

NETSock connection_get_sock(NETConnection connection) {
    return connection->sock;
}

void connection_set_sock(NETConnection connection, NETSock sock) {
    connection->sock = sock;
}

ADTList connection_get_in(NETConnection connection) {
    return connection->in;
}

void connection_set_in(NETConnection connection, ADTList in) {
    connection->in = in;
}

ADTList connection_get_out(NETConnection connection) {
    return connection->out;
}

void connection_set_out(NETConnection connection, ADTList out) {
    connection->out = out;
}

int connection_is_on(NETConnection connection) {
    return sock_is_on(connection->sock);
}

int connection_is_off(NETConnection connection) {
    return sock_is_off(connection->sock);
}

void connection_turn_off(NETConnection connection) {
    sock_turn_off(connection->sock);
}

ADTList connection_out(NETConnection connection) {
    return list_map(connection->out, (void *(*)(void *)) str_dup);
}

void connection_push(NETConnection connection, char *text) {
    list_append(connection->out, str_dup(text));
}

char *connection_pop(NETConnection connection) {
    return (char *) list_pop_front(connection->in);
}

void connection_send(NETConnection connection) {
    char *text = (char *) list_at(connection->out, 0);
    if (text && sock_send(connection->sock, text))
        list_full_remove_at(connection->out, 0, free);
}

void connection_recv(NETConnection connection) {
    char *text = sock_recv(connection->sock);
    if (text)
        list_append(connection->in, text);
}

void connection_loop(NETConnection connection) {
    if (sock_is_on(connection->sock)) {
        connection_send(connection);
        connection_recv(connection);
    }
}

int connection_list_poll(ADTList connections, int timeout) {
    int nfds = list_size(connections);
    int *pollin = (int *) memalloc(sizeof(int) * nfds);
    int *pollout = (int *) memalloc(sizeof(int) * nfds);
    NETSock *socks = (NETSock *) memalloc(sizeof(NETSock) * nfds);
    for (int i = 0; i < nfds; i++) {
        NETConnection connection = (NETConnection) list_at(connections, i);
        socks[i] = connection->sock;
        pollin[i] = 1;
        pollout[i] = (list_head(connection->out)) ? 1 : 0;
    }
    int result = sock_list_poll(socks, pollin, pollout, nfds, timeout);
    free(socks);
    free(pollin);
    free(pollout);
    return result;
}

