#include <stdlib.h>

#include "net/net.h"
#include "mem/mem.h"

NETNetwork network_new(int port, int connection_life, int client_poll_timeout,
                       int server_poll_timeout) {
    NETNetwork network = memalloc(sizeof(*network));
    network->client = client_new(connection_life, client_poll_timeout);
    network->server = server_listen(port, server_poll_timeout);
    return network;
}

void network_release(NETNetwork network) {
    client_release(network->client);
    server_release(network->server);
    free(network);
}

NETClient network_get_client(NETNetwork network) {
    return network->client;
}

void network_set_client(NETNetwork network, NETClient client) {
    network->client = client;
}

NETServer network_get_server(NETNetwork network) {
    return network->server;
}

void network_set_server(NETNetwork network, NETServer server) {
    network->server = server;
}

int network_port_is(NETNetwork network, int port) {
    return server_port_is(network->server, port);
}

int network_connection_life_is(NETNetwork network, int connection_life) {
    return client_connection_life_is(network->client, connection_life);
}

int network_client_poll_timeout_is(NETNetwork network, int client_poll_timeout) {
    return client_poll_timeout_is(network->client, client_poll_timeout);
}

int network_server_poll_timeout_is(NETNetwork network, int server_poll_timeout) {
    return server_poll_timeout_is(network->server, server_poll_timeout);
}

void network_reply(NETNetwork network, char *id, char *text) {
    server_push(network->server, id, text);
}

void network_send(NETNetwork network, NETAddress address, char *text) {
    client_push(network->client, address, text);
}

NETMessage network_recv(NETNetwork network) {
    return server_pop(network->server);
}

void network_loop(NETNetwork network) {
    client_loop(network->client);
    server_loop(network->server);
}

