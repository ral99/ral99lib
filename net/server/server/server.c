#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"

NETServer server_listen(int port, int poll_timeout) {
    NETServer server = (NETServer) memalloc(sizeof(*server));
    server->port = port;
    server->poll_timeout = poll_timeout;
    server->sock = sock_listen(port);
    server->connections = list_new();
    server->messages = list_new();
    return server;
}

void server_release(NETServer server) {
    sock_release(server->sock);
    list_full_release(server->connections,
                      (void (*)(void *)) server_connection_release);
    list_full_release(server->messages, (void (*)(void *)) message_release);
    free(server);
}

int server_get_port(NETServer server) {
    return server->port;
}

void server_set_port(NETServer server, int port) {
    server->port = port;
}

int server_get_poll_timeout(NETServer server) {
    return server->poll_timeout;
}

void server_set_poll_timeout(NETServer server, int poll_timeout) {
    server->poll_timeout = poll_timeout;
}

NETSock server_get_sock(NETServer server) {
    return server->sock;
}

void server_set_sock(NETServer server, NETSock sock) {
    server->sock = sock;
}

ADTList server_get_connections(NETServer server) {
    return server->connections;
}

void server_set_connections(NETServer server, ADTList connections) {
    server->connections = connections;
}

ADTList server_get_messages(NETServer server) {
    return server->messages;
}

void server_set_messages(NETServer server, ADTList in) {
    server->messages = in;
}

int server_port_is(NETServer server, int port) {
    return (server->port == port) ? 1 : 0;
}

int server_poll_timeout_is(NETServer server, int poll_timeout) {
    return (server->poll_timeout == poll_timeout) ? 1 : 0;
}

void server_accept(NETServer server) {
    NETServerConnection server_connection = accept_server_connection(server->sock);
    if (server_connection_is_on(server_connection))
        list_append(server->connections, server_connection);
    else
        server_connection_release(server_connection);
}

void server_push(NETServer server, char *id, char *text) {
    ADTListItem server_connection_item = list_find_cmp(server->connections,
                                                       (int (*)(void *, void *))
                                                       server_connection_id_is, id);
    if (server_connection_item)
        server_connection_push((NETServerConnection) list_value(server_connection_item), text);
}

NETMessage server_pop(NETServer server) {
    return (NETMessage) list_pop_front(server->messages);
}

void server_loop(NETServer server) {
    list_full_filter(server->connections, (int (*)(void *)) server_connection_is_on,
                     (void (*)(void *)) server_connection_release);
    server_connection_list_poll(server->connections, server->poll_timeout);
    list_foreach(server->connections, (void (*)(void *)) server_connection_loop);
    server_accept(server);
    for (ADTListItem it = list_head(server->connections); it; it = list_next(it)) {
        NETServerConnection server_connection = (NETServerConnection) list_value(it);
        char *text = server_connection_pop(server_connection);
        if (text) {
            char *id = server_connection_id(server_connection);
            list_append(server->messages, message_new(id, text));
            free(id);
            free(text);
        }
    }
}

