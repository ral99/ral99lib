#include <stdlib.h>

#include "net/client/client/client.h"
#include "net/client/client_connection/client_connection.h"
#include "net/address/address.h"
#include "util/util.h"
#include "adt/adt.h"

Client client_new(int connection_life, int poll_timeout) {
    Client client = memalloc(sizeof(*client));
    client->connections = list_new();
    client->connection_life = connection_life;
    client->poll_timeout = poll_timeout;
    return client;
}

void client_release(Client client) {
    list_full_release(client->connections,
                      (void (*)(void *)) client_connection_release);
    free(client);
}

List client_get_connections(Client client) {
    return client->connections;
}

void client_set_connections(Client client, List connections) {
    client->connections = connections;
}

int client_get_connection_life(Client client) {
    return client->connection_life;
}

void client_set_connection_life(Client client, int connection_life) {
    client->connection_life = connection_life;
}

int client_get_poll_timeout(Client client) {
    return client->poll_timeout;
}

void client_set_poll_timeout(Client client, int poll_timeout) {
    client->poll_timeout = poll_timeout;
}

int client_connection_life_is(Client client, int connection_life) {
    return (client->connection_life == connection_life) ? 1 : 0;
}

int client_poll_timeout_is(Client client, int poll_timeout) {
    return (client->poll_timeout == poll_timeout) ? 1 : 0;
}

ClientConnection client_get_connection(Client client, Address address) {
    ListItem client_connection_item = list_find_cmp(client->connections,
                                              (int (*)(void *, void*))
                                              client_connection_address_is, address);
    return (client_connection_item) ? list_value(client_connection_item) : NULL;
}

ClientConnection client_get_or_create_connection(Client client, Address address) {
    ClientConnection client_connection = client_get_connection(client, address);
    if (!client_connection) {
        client_connection = connect_client_connection(address,
                                                      client->connection_life);
        list_append(client->connections, client_connection);
    }
    return client_connection;
}

void client_push(Client client, Address address, char *text) {
    ClientConnection client_connection = client_get_or_create_connection(client,
                                                                         address);
    client_connection_lasts_for(client_connection, client->connection_life);
    client_connection_push(client_connection, text);
}

void client_loop(Client client) {
    list_full_filter(client->connections,
                     (int (*)(void *)) client_connection_is_alive,
                     (void (*)(void *)) client_connection_release);
    client_connection_list_poll(client->connections, client->poll_timeout);
    list_foreach(client->connections, (void (*)(void *)) client_connection_loop);
}

