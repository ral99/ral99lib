#ifndef __NET__SERVER__SERVER__
#define __NET__SERVER__SERVER__

#include "net/net.h"
#include "adt/adt.h"

typedef struct _NETServer *NETServer;
struct _NETServer {
    int port;
    int poll_timeout;
    NETSock sock;
    ADTList connections;
    ADTList messages;
};

/* Return a server listening on port. */
NETServer server_listen(int port, int poll_timeout);

/* Free the memory used by server and release its resources. */
void server_release(NETServer server);

/* Getter for port. */
int server_get_port(NETServer server);

/* Setter for port. */
void server_set_port(NETServer server, int port);

/* Getter for poll timeout. */
int server_get_poll_timeout(NETServer server);

/* Setter for poll timeout. */
void server_set_poll_timeout(NETServer server, int poll_timeout);

/* Getter for sock. */
NETSock server_get_sock(NETServer server);

/* Setter for sock. */
void server_set_sock(NETServer server, NETSock sock);

/* Getter for connections. */
ADTList server_get_connections(NETServer server);

/* Setter for connections. */
void server_set_connections(NETServer server, ADTList connections);

/* Getter for messages. */
ADTList server_get_messages(NETServer server);

/* Setter for messages. */
void server_set_messages(NETServer server, ADTList messages);

/* Boolean method for port. */
int server_port_is(NETServer server, int port);

/* Boolean method for poll timeout. */
int server_poll_timeout_is(NETServer server, int poll_timeout);

/* Call accept on server socket and establish a new connection. */
void server_accept(NETServer server);

/* Push a message to be sent by connection identified by id. */
void server_push(NETServer server, char *id, char *text);

/* Return a message received by server or NULL. */
NETMessage server_pop(NETServer server);

/* Poll, receive, send and remove off connections. */
void server_loop(NETServer server);

#endif

