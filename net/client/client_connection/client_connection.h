#ifndef __NET__CLIENT__CLIENT_CONNECTION__
#define __NET__CLIENT__CLIENT_CONNECTION__

#include <time.h>

#include "net/net.h"
#include "adt/adt.h"

typedef struct _NETClientConnection *NETClientConnection;
struct _NETClientConnection {
    NETAddress address;
    NETConnection connection;
    time_t expires;
};

/* Return a client connection to address living for life seconds. */
NETClientConnection connect_client_connection(NETAddress address, int life);

/* Free the memory used by client connection and release its resources. */
void client_connection_release(NETClientConnection client_connection);

/* Getter method for address. */
NETAddress client_connection_get_address(NETClientConnection client_connection);

/* Setter method for address. */
void client_connection_set_address(NETClientConnection client_connection, NETAddress address);

/* Getter method for connection. */
NETConnection client_connection_get_connection(NETClientConnection client_connection);

/* Setter method for connection. */
void client_connection_set_connection(NETClientConnection client_connection,
                                      NETConnection connection);

/* Getter method for expires. */
time_t client_connection_get_expires(NETClientConnection client_connection);

/* Setter method for expires. */
void client_connection_set_expires(NETClientConnection client_connection, time_t expires);

/* Boolean method for address. */
int client_connection_address_is(NETClientConnection client_connection, NETAddress address);

/* Return 1 if client connection is alive. 0, otherwise. */
int client_connection_is_alive(NETClientConnection client_connection);

/* Return 1 if client connection is dead. 0, otherwise. */
int client_connection_is_dead(NETClientConnection client_connection);

/* Return 1 if client connection is on. 0, otherwise. */
int client_connection_is_on(NETClientConnection client_connection);

/* Return 1 if client connection is off. 0, otherwise. */
int client_connection_is_off(NETClientConnection client_connection);

/* Turn the connection on. */
void client_connection_turn_on(NETClientConnection client_connection);

/* Turn the connection off. */
void client_connection_turn_off(NETClientConnection client_connection);

/* Set client connection life. */
void client_connection_lasts_for(NETClientConnection client_connection, int life);

/* Return a list of messages to be sent by client connection. */
ADTList client_connection_out(NETClientConnection client_connection);

/* Push a message to be sent by client connection. */
void client_connection_push(NETClientConnection client_connection, char *text);

/* Establish connection and send messages. */
void client_connection_loop(NETClientConnection client_connection);

/* Poll the client connection list and return the number of selected sockets. */
int client_connection_list_poll(ADTList client_connections, int timeout);

#endif

