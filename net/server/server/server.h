#ifndef __NET__SERVER__SERVER__
#define __NET__SERVER__SERVER__

#include "net/sock/sock.h"
#include "net/message/message.h"
#include "adt/adt.h"

typedef struct Server *Server;
struct Server {
    int port;
    int poll_timeout;
    Sock sock;
    List connections;
    List messages;
};

/* Return a server listening on port. */
Server server_listen(int port, int poll_timeout);

/* Free the memory used by server and release its resources. */
void server_release(Server server);

/* Getter for port. */
int server_get_port(Server server);

/* Setter for port. */
void server_set_port(Server server, int port);

/* Getter for poll timeout. */
int server_get_poll_timeout(Server server);

/* Setter for poll timeout. */
void server_set_poll_timeout(Server server, int poll_timeout);

/* Getter for sock. */
Sock server_get_sock(Server server);

/* Setter for sock. */
void server_set_sock(Server server, Sock sock);

/* Getter for connections. */
List server_get_connections(Server server);

/* Setter for connections. */
void server_set_connections(Server server, List connections);

/* Getter for messages. */
List server_get_messages(Server server);

/* Setter for messages. */
void server_set_messages(Server server, List messages);

/* Boolean method for port. */
int server_port_is(Server server, int port);

/* Boolean method for poll timeout. */
int server_poll_timeout_is(Server server, int poll_timeout);

/* Call accept on server socket and establish a new connection. */
void server_accept(Server server);

/* Push a message to be sent by connection identified by id. */
void server_push(Server server, char *id, char *text);

/* Return a message received by server or NULL. */
Message server_pop(Server server);

/* Poll, receive, send and remove off connections. */
void server_loop(Server server);

#endif

