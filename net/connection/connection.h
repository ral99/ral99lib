#ifndef __NET__CONNECTION__
#define __NET__CONNECTION__

#include "net/address/address.h"
#include "net/sock/sock.h"
#include "adt/adt.h"

typedef struct Connection *Connection;
struct Connection {
    Sock sock;
    List in, out;
};

/* Return a connection to address. */
Connection connection_connect(Address address);

/* Return a connection accepted by server. */
Connection connection_accept(Sock server_sock);

/* Free the memory used by connection and release its resources. */
void connection_release(Connection connection);

/* Getter method for sock. */
Sock connection_get_sock(Connection connection);

/* Setter method for sock. */
void connection_set_sock(Connection connection, Sock sock);

/* Getter method for in. */
List connection_get_in(Connection connection);

/* Setter method for in. */
void connection_set_in(Connection connection, List in);

/* Getter method for out. */
List connection_get_out(Connection connection);

/* Setter method for out. */
void connection_set_out(Connection connection, List out);

/* Return 1 if connection is on. 0, otherwise. */
int connection_is_on(Connection connection);

/* Return 1 if connection is off. 0, otherwise. */
int connection_is_off(Connection connection);

/* Turn the connection off. */
void connection_turn_off(Connection connection);

/* Return a list of messages to be sent by connection. */
List connection_out(Connection connection);

/* Push a message to be sent by connection. */
void connection_push(Connection connection, char *text);

/* Return a message received by connection or NULL. */
char *connection_pop(Connection connection);

/* Call send on socket. */
void connection_send(Connection connection);

/* Call recv on socket. */
void connection_recv(Connection connection);

/* Send and receive messages. */
void connection_loop(Connection connection);

/* Poll the connection list and return the number of selected sockets. */
int connection_list_poll(List connections, int timeout);

#endif

