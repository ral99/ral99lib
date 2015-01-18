#ifndef __NET__CLIENT__CLIENT_CONNECTION__
#define __NET__CLIENT__CLIENT_CONNECTION__

#include <time.h>

#include "net/net.h"
#include "adt/adt.h"

typedef struct ClientConnection *ClientConnection;
struct ClientConnection {
    Address address;
    Connection connection;
    time_t expires;
};

/* Return a client connection to address living for life seconds. */
ClientConnection connect_client_connection(Address address, int life);

/* Free the memory used by client connection and release its resources. */
void client_connection_release(ClientConnection client_connection);

/* Getter method for address. */
Address client_connection_get_address(ClientConnection client_connection);

/* Setter method for address. */
void client_connection_set_address(ClientConnection client_connection,
                                   Address address);

/* Getter method for connection. */
Connection client_connection_get_connection(ClientConnection client_connection);

/* Setter method for connection. */
void client_connection_set_connection(ClientConnection client_connection,
                                      Connection connection);

/* Getter method for expires. */
time_t client_connection_get_expires(ClientConnection client_connection);

/* Setter method for expires. */
void client_connection_set_expires(ClientConnection client_connection,
                                   time_t expires);

/* Boolean method for address. */
int client_connection_address_is(ClientConnection client_connection,
                                 Address address);

/* Return 1 if client connection is alive. 0, otherwise. */
int client_connection_is_alive(ClientConnection client_connection);

/* Return 1 if client connection is dead. 0, otherwise. */
int client_connection_is_dead(ClientConnection client_connection);

/* Return 1 if client connection is on. 0, otherwise. */
int client_connection_is_on(ClientConnection client_connection);

/* Return 1 if client connection is off. 0, otherwise. */
int client_connection_is_off(ClientConnection client_connection);

/* Turn the connection on. */
void client_connection_turn_on(ClientConnection client_connection);

/* Turn the connection off. */
void client_connection_turn_off(ClientConnection client_connection);

/* Set client connection life. */
void client_connection_lasts_for(ClientConnection client_connection, int life);

/* Return a list of messages to be sent by client connection. */
List client_connection_out(ClientConnection client_connection);

/* Push a message to be sent by client connection. */
void client_connection_push(ClientConnection client_connection, char *text);

/* Establish connection and send messages. */
void client_connection_loop(ClientConnection client_connection);

/* Poll the client connection list and return the number of selected sockets. */
int client_connection_list_poll(List client_connections, int timeout);

#endif

