#ifndef __NET__NETWORK__
#define __NET__NETWORK__

#include "net/net.h"

typedef struct Network *Network;
struct Network {
    Client client;
    Server server;
};

/* Return a network listening to connections on port. */
Network network_new(int port, int connection_life, int client_poll_timeout,
                    int server_poll_timeout);

/* Free the memory used by network and release its resources. */
void network_release(Network network);

/* Getter method for client. */
Client network_get_client(Network network);

/* Setter method for client. */
void network_set_client(Network network, Client client);

/* Getter method for server. */
Server network_get_server(Network network);

/* Setter method for server. */
void network_set_server(Network network, Server server);

/* Boolean method for port. */
int network_port_is(Network network, int port);

/* Boolean method for connection life. */
int network_connection_life_is(Network network, int connection_life);

/* Boolean method for client poll timeout. */
int network_client_poll_timeout_is(Network network, int client_poll_timeout);

/* Boolean method for server poll timeout. */
int network_server_poll_timeout_is(Network network, int server_poll_timeout);

/* Reply message to the connection identified by id. */
void network_reply(Network network, char *id, char *text);

/* Send message to address. */
void network_send(Network network, Address address, char *text);

/* Return a message received or NULL. */
Message network_recv(Network network);

/* Send and receive messages. */
void network_loop(Network network);

#endif

