#ifndef __NET__NETWORK__
#define __NET__NETWORK__

#include "net/net.h"

typedef struct _NETNetwork *NETNetwork;
struct _NETNetwork {
    NETClient client;
    NETServer server;
};

/* Return a network listening to connections on port. */
NETNetwork network_new(int port, int connection_life, int client_poll_timeout,
                       int server_poll_timeout);

/* Free the memory used by network and release its resources. */
void network_release(NETNetwork network);

/* Getter method for client. */
NETClient network_get_client(NETNetwork network);

/* Setter method for client. */
void network_set_client(NETNetwork network, NETClient client);

/* Getter method for server. */
NETServer network_get_server(NETNetwork network);

/* Setter method for server. */
void network_set_server(NETNetwork network, NETServer server);

/* Boolean method for port. */
int network_port_is(NETNetwork network, int port);

/* Boolean method for connection life. */
int network_connection_life_is(NETNetwork network, int connection_life);

/* Boolean method for client poll timeout. */
int network_client_poll_timeout_is(NETNetwork network, int client_poll_timeout);

/* Boolean method for server poll timeout. */
int network_server_poll_timeout_is(NETNetwork network, int server_poll_timeout);

/* Reply message to the connection identified by id. */
void network_reply(NETNetwork network, char *id, char *text);

/* Send message to address. */
void network_send(NETNetwork network, NETAddress address, char *text);

/* Return a message received or NULL. */
NETMessage network_recv(NETNetwork network);

/* Send and receive messages. */
void network_loop(NETNetwork network);

#endif

