#include <stdlib.h>
#include <time.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"

NETClientConnection connect_client_connection(NETAddress address, int life) {
    NETClientConnection client_connection =
        (NETClientConnection) memalloc(sizeof(*client_connection));
    client_connection->address = address_dup(address);
    client_connection->connection = connection_connect(address);
    client_connection->expires = time(NULL) + life;
    return client_connection;
}

void client_connection_release(NETClientConnection client_connection) {
    address_release(client_connection->address);
    connection_release(client_connection->connection);
    free(client_connection);
}

NETAddress client_connection_get_address(NETClientConnection client_connection) {
    return client_connection->address;
}

void client_connection_set_address(NETClientConnection client_connection,
                                   NETAddress address) {
    client_connection->address = address;
}

NETConnection client_connection_get_connection(NETClientConnection client_connection) {
    return client_connection->connection;
}

void client_connection_set_connection(NETClientConnection client_connection,
                                      NETConnection connection) {
    client_connection->connection = connection;
}

time_t client_connection_get_expires(NETClientConnection client_connection) {
    return client_connection->expires;
}

void client_connection_set_expires(NETClientConnection client_connection, time_t expires) {
    client_connection->expires = expires;
}

int client_connection_address_is(NETClientConnection client_connection, NETAddress address) {
    return address_equals(client_connection->address, address);
}

int client_connection_is_alive(NETClientConnection client_connection) {
    return (client_connection->expires > time(NULL)) ? 1 : 0;
}

int client_connection_is_dead(NETClientConnection client_connection) {
    return (client_connection_is_alive(client_connection)) ? 0 : 1;
}

int client_connection_is_on(NETClientConnection client_connection) {
    return connection_is_on(client_connection->connection);
}

int client_connection_is_off(NETClientConnection client_connection) {
    return connection_is_off(client_connection->connection);
}

void client_connection_turn_on(NETClientConnection client_connection) {
    ADTList out = connection_out(client_connection->connection);
    NETConnection connection = connection_connect(client_connection->address);
    for (ADTListItem it = list_head(out); it; it = it->next)
        connection_push(connection, (char *) list_value(it));
    list_full_release(out, free);
    connection_release(client_connection->connection);
    client_connection->connection = connection;
}

void client_connection_turn_off(NETClientConnection client_connection) {
    connection_turn_off(client_connection->connection);
}

void client_connection_lasts_for(NETClientConnection client_connection, int life) {
    client_connection->expires = time(NULL) + life;
}

ADTList client_connection_out(NETClientConnection client_connection) {
    return connection_out(client_connection->connection);
}

void client_connection_push(NETClientConnection client_connection, char *text) {
    connection_push(client_connection->connection, text);
}

void client_connection_loop(NETClientConnection client_connection) {
    connection_loop(client_connection->connection);
    free(connection_pop(client_connection->connection));
    if (connection_is_off(client_connection->connection))
        client_connection_turn_on(client_connection);
}

int client_connection_list_poll(ADTList client_connections, int timeout) {
    ADTList connections = list_map(client_connections,
                          (void *(*)(void *)) client_connection_get_connection);
    int result = connection_list_poll(connections, timeout);
    list_release(connections);
    return result;
}

