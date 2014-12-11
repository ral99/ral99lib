#ifndef __NET__CLIENT__CLIENT__
#define __NET__CLIENT__CLIENT__

#include "net/client/client_connection/client_connection.h"
#include "net/address/address.h"
#include "adt/adt.h"

typedef struct Client *Client;
struct Client {
    List connections;
    int connection_life;
    int poll_timeout;
};

/* Return a new client. */
Client client_new(int connection_life, int poll_timeout);

/* Free the memory used by client and release its resources. */
void client_release(Client client);

/* Getter method for connections. */
List client_get_connections(Client client);

/* Setter method for connections. */
void client_set_connections(Client client, List connections);

/* Getter method for connection life. */
int client_get_connection_life(Client client);

/* Setter method for poll timeout. */
void client_set_connection_life(Client client, int connection_life);

/* Getter method for poll timeout. */
int client_get_poll_timeout(Client client);

/* Setter method for poll timeout. */
void client_set_poll_timeout(Client client, int poll_timeout);

/* Boolean method for connection life. */
int client_connection_life_is(Client client, int connection_life);

/* Boolean method for poll timeout. */
int client_poll_timeout_is(Client client, int poll_timeout);

/* Return a client connection connected to address or NULL. */
ClientConnection client_get_connection(Client client, Address address);

/* Return a client connection connected to address. */
ClientConnection client_get_or_create_connection(Client client, Address address);

/* Push a message to be sent to address. */
void client_push(Client client, Address address, char *text);

/* Poll, establish, receive, send and remove connections. */
void client_loop(Client client);

#endif

