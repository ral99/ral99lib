#ifndef __NET__SOCK__
#define __NET__SOCK__

#include "net/net.h"

typedef struct _NETSock *NETSock;
struct _NETSock {
    int fd;
    int on;
};

/* Return a new socket. */
NETSock sock_new(int fd, int on);

/* Return a new nonblocking socket. */
NETSock sock_nonblocking(int fd);

/* Return a socket listening for incoming connections on port. */
NETSock sock_listen(int port);

/* Return a socket accepted by server. */
NETSock sock_accept(NETSock server_sock);

/* Return a socket connected to address. */
NETSock sock_connect(NETAddress address);

/* Free the memory used by socket and release its resources. */
void sock_release(NETSock sock);

/* Getter method for fd. */
int sock_get_fd(NETSock sock);

/* Setter method for fd. */
void sock_set_fd(NETSock sock, int fd);

/* Getter method for on. */
int sock_get_on(NETSock sock);

/* Setter method for on. */
void sock_set_on(NETSock sock, int on);

/* Boolean method for fd. */
int sock_fd_is(NETSock sock, int fd);

/* Return 1 if socket is on. 0, otherwise. */
int sock_is_on(NETSock sock);

/* Return 1 if socket is off. 0, otherwise. */
int sock_is_off(NETSock sock);

/* Turn the socket off. */
void sock_turn_off(NETSock sock);

/* Return 1 if message was sent. 0, otherwise. */
int sock_send(NETSock sock, char *text);

/* Return a message received by socket or NULL. */
char *sock_recv(NETSock sock);

/* Poll the socket array and return the number of selected sockets. */
int sock_list_poll(NETSock socks[], int pollin[], int pollout[], int nfds, int timeout);

#endif

