#ifndef __NET__SERVER__SERVER_CONNECTION__
#define __NET__SERVER__SERVER_CONNECTION__

#include "net/net.h"
#include "adt/adt.h"

#define SERVER_CONNECTION_ID_LENGTH 32

typedef struct _NETServerConnection *NETServerConnection;
struct _NETServerConnection {
    char *id;
    NETConnection connection;
};

/* Return a server connection accepted by server. */
NETServerConnection accept_server_connection(NETSock server_sock);

/* Free the memory used by server connection and release its resources. */
void server_connection_release(NETServerConnection server_connection);

/* Getter method for id. */
char *server_connection_get_id(NETServerConnection server_connection);

/* Setter method for id. */
void server_connection_set_id(NETServerConnection server_connection, char *id);

/* Getter method for connection. */
NETConnection server_connection_get_connection(NETServerConnection server_connection);

/* Setter method for connection. */
void server_connection_set_connection(NETServerConnection server_connection,
                                      NETConnection connection);

/* Boolean method for id. */
int server_connection_id_is(NETServerConnection server_connection, char *id);

/* Return server connection id. */
char *server_connection_id(NETServerConnection server_connection);

/* Return 1 if server connection is on. 0, otherwise. */
int server_connection_is_on(NETServerConnection server_connection);

/* Return 1 if server connection is off. 0, otherwise. */
int server_connection_is_off(NETServerConnection server_connection);

/* Turn the server connection off. */
void server_connection_turn_off(NETServerConnection server_connection);

/* Return a list of messages to be sent by server connection. */
ADTList server_connection_out(NETServerConnection server_connection);

/* Push a message to be sent by server connection. */
void server_connection_push(NETServerConnection server_connection, char *text);

/* Return a message received by server connection or NULL. */
char *server_connection_pop(NETServerConnection server_connection);

/* Send and receive messages. */
void server_connection_loop(NETServerConnection server_connection);

/* Poll the server connection list and return the number of selected sockets. */
int server_connection_list_poll(ADTList server_connections, int timeout);

#endif

