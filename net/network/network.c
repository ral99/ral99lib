#include <stdlib.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"

Network network_new(int port, int connection_life, int client_poll_timeout,
                    int server_poll_timeout) {
    Network network = memalloc(sizeof(*network));
    network->client = client_new(connection_life, client_poll_timeout);
    network->server = server_listen(port, server_poll_timeout);
    return network;
}

void network_release(Network network) {
    client_release(network->client);
    server_release(network->server);
    free(network);
}

Client network_get_client(Network network) {
    return network->client;
}

void network_set_client(Network network, Client client) {
    network->client = client;
}

Server network_get_server(Network network) {
    return network->server;
}

void network_set_server(Network network, Server server) {
    network->server = server;
}

int network_port_is(Network network, int port) {
    return server_port_is(network->server, port);
}

int network_connection_life_is(Network network, int connection_life) {
    return client_connection_life_is(network->client, connection_life);
}

int network_client_poll_timeout_is(Network network, int client_poll_timeout) {
    return client_poll_timeout_is(network->client, client_poll_timeout);
}

int network_server_poll_timeout_is(Network network, int server_poll_timeout) {
    return server_poll_timeout_is(network->server, server_poll_timeout);
}

void network_reply(Network network, char *id, char *text) {
    server_push(network->server, id, text);
}

void network_send(Network network, Address address, char *text) {
    client_push(network->client, address, text);
}

Message network_recv(Network network) {
    return server_pop(network->server);
}

void network_loop(Network network) {
    client_loop(network->client);
    server_loop(network->server);
}

