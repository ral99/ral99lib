#ifndef __NET__CONNECTION__
#define __NET__CONNECTION__

#include "net/net.h"
#include "adt/adt.h"

typedef struct _NETConnection *NETConnection;
struct _NETConnection {
    NETSock sock;
    ADTList in, out;
};

/* Return a connection to address. */
NETConnection connection_connect(NETAddress address);

/* Return a connection accepted by server. */
NETConnection connection_accept(NETSock server_sock);

/* Free the memory used by connection and release its resources. */
void connection_release(NETConnection connection);

/* Getter method for sock. */
NETSock connection_get_sock(NETConnection connection);

/* Setter method for sock. */
void connection_set_sock(NETConnection connection, NETSock sock);

/* Getter method for in. */
ADTList connection_get_in(NETConnection connection);

/* Setter method for in. */
void connection_set_in(NETConnection connection, ADTList in);

/* Getter method for out. */
ADTList connection_get_out(NETConnection connection);

/* Setter method for out. */
void connection_set_out(NETConnection connection, ADTList out);

/* Return 1 if connection is on. 0, otherwise. */
int connection_is_on(NETConnection connection);

/* Return 1 if connection is off. 0, otherwise. */
int connection_is_off(NETConnection connection);

/* Turn the connection off. */
void connection_turn_off(NETConnection connection);

/* Return a list of messages to be sent by connection. */
ADTList connection_out(NETConnection connection);

/* Push a message to be sent by connection. */
void connection_push(NETConnection connection, char *text);

/* Return a message received by connection or NULL. */
char *connection_pop(NETConnection connection);

/* Call send on socket. */
void connection_send(NETConnection connection);

/* Call recv on socket. */
void connection_recv(NETConnection connection);

/* Send and receive messages. */
void connection_loop(NETConnection connection);

/* Poll the connection list and return the number of selected sockets. */
int connection_list_poll(ADTList connections, int timeout);

#endif

