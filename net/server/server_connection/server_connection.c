#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "str/str.h"

ServerConnection accept_server_connection(Sock server_sock) {
    ServerConnection server_connection = memalloc(sizeof(*server_connection));
    server_connection->id = str_random(SERVER_CONNECTION_ID_LENGTH);
    server_connection->connection = connection_accept(server_sock);
    return server_connection;
}

void server_connection_release(ServerConnection server_connection) {
    free(server_connection->id);
    connection_release(server_connection->connection);
    free(server_connection);
}

char *server_connection_get_id(ServerConnection server_connection) {
    return server_connection->id;
}

void server_connection_set_id(ServerConnection server_connection, char *id) {
    server_connection->id = id;
}

Connection server_connection_get_connection(ServerConnection server_connection) {
    return server_connection->connection;
}

void server_connection_set_connection(ServerConnection server_connection,
                                      Connection connection) {
    server_connection->connection = connection;
}

int server_connection_id_is(ServerConnection server_connection, char *id) {
    return str_equals(server_connection->id, id);
}

char *server_connection_id(ServerConnection server_connection) {
    return str_dup(server_connection->id);
}

int server_connection_is_on(ServerConnection server_connection) {
    return connection_is_on(server_connection->connection);
}

int server_connection_is_off(ServerConnection server_connection) {
    return connection_is_off(server_connection->connection);
}

void server_connection_turn_off(ServerConnection server_connection) {
    connection_turn_off(server_connection->connection);
}

List server_connection_out(ServerConnection server_connection) {
    return connection_out(server_connection->connection);
}

void server_connection_push(ServerConnection server_connection, char *text) {
    connection_push(server_connection->connection, text);
}

char *server_connection_pop(ServerConnection server_connection) {
    return connection_pop(server_connection->connection);
}

void server_connection_loop(ServerConnection server_connection) {
    connection_loop(server_connection->connection);
}

int server_connection_list_poll(List server_connections, int timeout) {
    List connections = list_map(server_connections,
                          (void *(*)(void *)) server_connection_get_connection);
    int result = connection_list_poll(connections, timeout);
    list_release(connections);
    return result;
}

