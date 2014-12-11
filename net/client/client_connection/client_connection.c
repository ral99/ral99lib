#include <stdlib.h>
#include <time.h>

#include "net/client/client_connection/client_connection.h"
#include "net/address/address.h"
#include "net/connection/connection.h"
#include "util/util.h"
#include "adt/adt.h"

ClientConnection connect_client_connection(Address address, int life) {
    ClientConnection client_connection = memalloc(sizeof(*client_connection));
    client_connection->address = address_dup(address);
    client_connection->connection = connection_connect(address);
    client_connection->expires = time(NULL) + life;
    return client_connection;
}

void client_connection_release(ClientConnection client_connection) {
    address_release(client_connection->address);
    connection_release(client_connection->connection);
    free(client_connection);
}

Address client_connection_get_address(ClientConnection client_connection) {
    return client_connection->address;
}

void client_connection_set_address(ClientConnection client_connection,
                                   Address address) {
    client_connection->address = address;
}

Connection client_connection_get_connection(ClientConnection client_connection) {
    return client_connection->connection;
}

void client_connection_set_connection(ClientConnection client_connection,
                                      Connection connection) {
    client_connection->connection = connection;
}

time_t client_connection_get_expires(ClientConnection client_connection) {
    return client_connection->expires;
}

void client_connection_set_expires(ClientConnection client_connection,
                                   time_t expires) {
    client_connection->expires = expires;
}

int client_connection_address_is(ClientConnection client_connection,
                                 Address address) {
    return address_equals(client_connection->address, address);
}

int client_connection_is_alive(ClientConnection client_connection) {
    return (client_connection->expires > time(NULL)) ? 1 : 0;
}

int client_connection_is_dead(ClientConnection client_connection) {
    return (client_connection_is_alive(client_connection)) ? 0 : 1;
}

int client_connection_is_on(ClientConnection client_connection) {
    return connection_is_on(client_connection->connection);
}

int client_connection_is_off(ClientConnection client_connection) {
    return connection_is_off(client_connection->connection);
}

void client_connection_turn_on(ClientConnection client_connection) {
    List out = connection_out(client_connection->connection);
    Connection connection = connection_connect(client_connection->address);
    for (ListItem it = list_head(out); it; it = it->next)
        connection_push(connection, list_value(it));
    list_full_release(out, free);
    connection_release(client_connection->connection);
    client_connection->connection = connection;
}

void client_connection_turn_off(ClientConnection client_connection) {
    connection_turn_off(client_connection->connection);
}

void client_connection_lasts_for(ClientConnection client_connection, int life) {
    client_connection->expires = time(NULL) + life;
}

List client_connection_out(ClientConnection client_connection) {
    return connection_out(client_connection->connection);
}

void client_connection_push(ClientConnection client_connection, char *text) {
    connection_push(client_connection->connection, text);
}

void client_connection_loop(ClientConnection client_connection) {
    connection_loop(client_connection->connection);
    free(connection_pop(client_connection->connection));
    if (connection_is_off(client_connection->connection))
        client_connection_turn_on(client_connection);
}

int client_connection_list_poll(List client_connections, int timeout) {
    List connections = list_map(client_connections,
                          (void *(*)(void *)) client_connection_get_connection);
    int result = connection_list_poll(connections, timeout);
    list_release(connections);
    return result;
}

