#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"

Server server_listen(int port, int poll_timeout) {
    Server server = memalloc(sizeof(*server));
    server->port = port;
    server->poll_timeout = poll_timeout;
    server->sock = sock_listen(port);
    server->connections = list_new();
    server->messages = list_new();
    return server;
}

void server_release(Server server) {
    sock_release(server->sock);
    list_full_release(server->connections,
                      (void (*)(void *)) server_connection_release);
    list_full_release(server->messages, (void (*)(void *)) message_release);
    free(server);
}

int server_get_port(Server server) {
    return server->port;
}

void server_set_port(Server server, int port) {
    server->port = port;
}

int server_get_poll_timeout(Server server) {
    return server->poll_timeout;
}

void server_set_poll_timeout(Server server, int poll_timeout) {
    server->poll_timeout = poll_timeout;
}

Sock server_get_sock(Server server) {
    return server->sock;
}

void server_set_sock(Server server, Sock sock) {
    server->sock = sock;
}

List server_get_connections(Server server) {
    return server->connections;
}

void server_set_connections(Server server, List connections) {
    server->connections = connections;
}

List server_get_messages(Server server) {
    return server->messages;
}

void server_set_messages(Server server, List in) {
    server->messages = in;
}

int server_port_is(Server server, int port) {
    return (server->port == port) ? 1 : 0;
}

int server_poll_timeout_is(Server server, int poll_timeout) {
    return (server->poll_timeout == poll_timeout) ? 1 : 0;
}

void server_accept(Server server) {
    ServerConnection server_connection = accept_server_connection(server->sock);
    if (server_connection_is_on(server_connection))
        list_append(server->connections, server_connection);
    else
        server_connection_release(server_connection);
}

void server_push(Server server, char *id, char *text) {
    ListItem server_connection_item = list_find_cmp(server->connections,
                                              (int (*)(void *, void *))
                                              server_connection_id_is, id);
    if (server_connection_item)
        server_connection_push(list_value(server_connection_item), text);
}

Message server_pop(Server server) {
    return list_pop_front(server->messages);
}

void server_loop(Server server) {
    list_full_filter(server->connections, (int (*)(void *)) server_connection_is_on,
                     (void (*)(void *)) server_connection_release);
    server_connection_list_poll(server->connections, server->poll_timeout);
    list_foreach(server->connections, (void (*)(void *)) server_connection_loop);
    server_accept(server);
    for (ListItem it = list_head(server->connections); it; it = list_next(it)) {
        ServerConnection server_connection = list_value(it);
        char *text = server_connection_pop(server_connection);
        if (text) {
            char *id = server_connection_id(server_connection);
            list_append(server->messages, message_new(id, text));
            free(id);
            free(text);
        }
    }
}

