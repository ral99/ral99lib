#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"

NETClient client_new(int connection_life, int poll_timeout) {
    NETClient client = memalloc(sizeof(*client));
    client->connections = list_new();
    client->connection_life = connection_life;
    client->poll_timeout = poll_timeout;
    return client;
}

void client_release(NETClient client) {
    list_full_release(client->connections,
                      (void (*)(void *)) client_connection_release);
    free(client);
}

ADTList client_get_connections(NETClient client) {
    return client->connections;
}

void client_set_connections(NETClient client, ADTList connections) {
    client->connections = connections;
}

int client_get_connection_life(NETClient client) {
    return client->connection_life;
}

void client_set_connection_life(NETClient client, int connection_life) {
    client->connection_life = connection_life;
}

int client_get_poll_timeout(NETClient client) {
    return client->poll_timeout;
}

void client_set_poll_timeout(NETClient client, int poll_timeout) {
    client->poll_timeout = poll_timeout;
}

int client_connection_life_is(NETClient client, int connection_life) {
    return (client->connection_life == connection_life) ? 1 : 0;
}

int client_poll_timeout_is(NETClient client, int poll_timeout) {
    return (client->poll_timeout == poll_timeout) ? 1 : 0;
}

NETClientConnection client_get_connection(NETClient client, NETAddress address) {
    ADTListItem client_connection_item = list_find_cmp(client->connections,
                                              (int (*)(void *, void*))
                                              client_connection_address_is, address);
    return (client_connection_item) ? list_value(client_connection_item) : NULL;
}

NETClientConnection client_get_or_create_connection(NETClient client, NETAddress address) {
    NETClientConnection client_connection = client_get_connection(client, address);
    if (!client_connection) {
        client_connection = connect_client_connection(address,
                                                      client->connection_life);
        list_append(client->connections, client_connection);
    }
    return client_connection;
}

void client_push(NETClient client, NETAddress address, char *text) {
    NETClientConnection client_connection = client_get_or_create_connection(client,
                                                                         address);
    client_connection_lasts_for(client_connection, client->connection_life);
    client_connection_push(client_connection, text);
}

void client_loop(NETClient client) {
    list_full_filter(client->connections,
                     (int (*)(void *)) client_connection_is_alive,
                     (void (*)(void *)) client_connection_release);
    client_connection_list_poll(client->connections, client->poll_timeout);
    list_foreach(client->connections, (void (*)(void *)) client_connection_loop);
}

