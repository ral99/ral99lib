#ifndef __NET__SOCK__
#define __NET__SOCK__

#include "net/net.h"

typedef struct Sock *Sock;
struct Sock {
    int fd;
    int on;
};

/* Return a new socket. */
Sock sock_new(int fd, int on);

/* Return a new nonblocking socket. */
Sock sock_nonblocking(int fd);

/* Return a socket listening for incoming connections on port. */
Sock sock_listen(int port);

/* Return a socket accepted by server. */
Sock sock_accept(Sock server_sock);

/* Return a socket connected to address. */
Sock sock_connect(Address address);

/* Free the memory used by socket and release its resources. */
void sock_release(Sock sock);

/* Getter method for fd. */
int sock_get_fd(Sock sock);

/* Setter method for fd. */
void sock_set_fd(Sock sock, int fd);

/* Getter method for on. */
int sock_get_on(Sock sock);

/* Setter method for on. */
void sock_set_on(Sock sock, int on);

/* Boolean method for fd. */
int sock_fd_is(Sock sock, int fd);

/* Return 1 if socket is on. 0, otherwise. */
int sock_is_on(Sock sock);

/* Return 1 if socket is off. 0, otherwise. */
int sock_is_off(Sock sock);

/* Turn the socket off. */
void sock_turn_off(Sock sock);

/* Return 1 if message was sent. 0, otherwise. */
int sock_send(Sock sock, char *text);

/* Return a message received by socket or NULL. */
char *sock_recv(Sock sock);

/* Poll the socket array and return the number of selected sockets. */
int sock_list_poll(Sock socks[], int pollin[], int pollout[], int nfds,
                     int timeout);

#endif

