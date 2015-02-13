#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "str/str.h"

NETServerConnection accept_server_connection(NETSock server_sock) {
    NETServerConnection server_connection =
        (NETServerConnection) memalloc(sizeof(*server_connection));
    server_connection->id = str_random(SERVER_CONNECTION_ID_LENGTH);
    server_connection->connection = connection_accept(server_sock);
    return server_connection;
}

void server_connection_release(NETServerConnection server_connection) {
    free(server_connection->id);
    connection_release(server_connection->connection);
    free(server_connection);
}

char *server_connection_get_id(NETServerConnection server_connection) {
    return server_connection->id;
}

void server_connection_set_id(NETServerConnection server_connection, char *id) {
    server_connection->id = id;
}

NETConnection server_connection_get_connection(NETServerConnection server_connection) {
    return server_connection->connection;
}

void server_connection_set_connection(NETServerConnection server_connection,
                                      NETConnection connection) {
    server_connection->connection = connection;
}

int server_connection_id_is(NETServerConnection server_connection, char *id) {
    return str_equals(server_connection->id, id);
}

char *server_connection_id(NETServerConnection server_connection) {
    return str_dup(server_connection->id);
}

int server_connection_is_on(NETServerConnection server_connection) {
    return connection_is_on(server_connection->connection);
}

int server_connection_is_off(NETServerConnection server_connection) {
    return connection_is_off(server_connection->connection);
}

void server_connection_turn_off(NETServerConnection server_connection) {
    connection_turn_off(server_connection->connection);
}

ADTList server_connection_out(NETServerConnection server_connection) {
    return connection_out(server_connection->connection);
}

void server_connection_push(NETServerConnection server_connection, char *text) {
    connection_push(server_connection->connection, text);
}

char *server_connection_pop(NETServerConnection server_connection) {
    return connection_pop(server_connection->connection);
}

void server_connection_loop(NETServerConnection server_connection) {
    connection_loop(server_connection->connection);
}

int server_connection_list_poll(ADTList server_connections, int timeout) {
    ADTList connections = list_map(server_connections,
                          (void *(*)(void *)) server_connection_get_connection);
    int result = connection_list_poll(connections, timeout);
    list_release(connections);
    return result;
}

