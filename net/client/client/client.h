#ifndef __NET__CLIENT__CLIENT__
#define __NET__CLIENT__CLIENT__

#include "net/net.h"
#include "adt/adt.h"

typedef struct _NETClient *NETClient;
struct _NETClient {
    ADTList connections;
    int connection_life;
    int poll_timeout;
};

/* Return a new client. */
NETClient client_new(int connection_life, int poll_timeout);

/* Free the memory used by client and release its resources. */
void client_release(NETClient client);

/* Getter method for connections. */
ADTList client_get_connections(NETClient client);

/* Setter method for connections. */
void client_set_connections(NETClient client, ADTList connections);

/* Getter method for connection life. */
int client_get_connection_life(NETClient client);

/* Setter method for poll timeout. */
void client_set_connection_life(NETClient client, int connection_life);

/* Getter method for poll timeout. */
int client_get_poll_timeout(NETClient client);

/* Setter method for poll timeout. */
void client_set_poll_timeout(NETClient client, int poll_timeout);

/* Boolean method for connection life. */
int client_connection_life_is(NETClient client, int connection_life);

/* Boolean method for poll timeout. */
int client_poll_timeout_is(NETClient client, int poll_timeout);

/* Return a client connection connected to address or NULL. */
NETClientConnection client_get_connection(NETClient client, NETAddress address);

/* Return a client connection connected to address. */
NETClientConnection client_get_or_create_connection(NETClient client, NETAddress address);

/* Push a message to be sent to address. */
void client_push(NETClient client, NETAddress address, char *text);

/* Poll, establish, receive, send and remove connections. */
void client_loop(NETClient client);

#endif

