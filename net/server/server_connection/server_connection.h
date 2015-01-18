#ifndef __NET__SERVER__SERVER_CONNECTION__
#define __NET__SERVER__SERVER_CONNECTION__

#include "net/net.h"
#include "adt/adt.h"

#define SERVER_CONNECTION_ID_LENGTH 32

typedef struct ServerConnection *ServerConnection;
struct ServerConnection {
    char *id;
    Connection connection;
};

/* Return a server connection accepted by server. */
ServerConnection accept_server_connection(Sock server_sock);

/* Free the memory used by server connection and release its resources. */
void server_connection_release(ServerConnection server_connection);

/* Getter method for id. */
char *server_connection_get_id(ServerConnection server_connection);

/* Setter method for id. */
void server_connection_set_id(ServerConnection server_connection, char *id);

/* Getter method for connection. */
Connection server_connection_get_connection(ServerConnection server_connection);

/* Setter method for connection. */
void server_connection_set_connection(ServerConnection server_connection,
                                      Connection connection);

/* Boolean method for id. */
int server_connection_id_is(ServerConnection server_connection, char *id);

/* Return server connection id. */
char *server_connection_id(ServerConnection server_connection);

/* Return 1 if server connection is on. 0, otherwise. */
int server_connection_is_on(ServerConnection server_connection);

/* Return 1 if server connection is off. 0, otherwise. */
int server_connection_is_off(ServerConnection server_connection);

/* Turn the server connection off. */
void server_connection_turn_off(ServerConnection server_connection);

/* Return a list of messages to be sent by server connection. */
List server_connection_out(ServerConnection server_connection);

/* Push a message to be sent by server connection. */
void server_connection_push(ServerConnection server_connection, char *text);

/* Return a message received by server connection or NULL. */
char *server_connection_pop(ServerConnection server_connection);

/* Send and receive messages. */
void server_connection_loop(ServerConnection server_connection);

/* Poll the server connection list and return the number of selected sockets. */
int server_connection_list_poll(List server_connections, int timeout);

#endif

