#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "net/net.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "str/str.h"

NETSock sock_new(int fd, int on) {
    NETSock sock = (NETSock) memalloc(sizeof(*sock));
    sock->fd = fd;
    sock->on = on;
    return sock;
}

NETSock sock_nonblocking(int fd) {
    NETSock sock = sock_new(fd, 1);
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        sock_turn_off(sock);
    return sock;
}

NETSock sock_listen(int port) {
    #ifdef __APPLE__
    int set = 1;
    #endif
    int reuse = 1;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    NETSock sock = sock_nonblocking(fd);
    NETAddress address = address_new((char *) "127.0.0.1", port);
    struct sockaddr *sockaddr = address_sockaddr(address);
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0 ||
        #ifdef __APPLE__
        setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &set, sizeof(set)) < 0 ||
        #endif
        bind(fd, sockaddr, sizeof(*sockaddr)) < 0 ||
        listen(fd, 50) < 0)
        sock_turn_off(sock);
    free(sockaddr);
    address_release(address);
    return sock;
}

NETSock sock_accept(NETSock server_sock) {
    int fd = accept(server_sock->fd, NULL, NULL);
    if (fd < 0 && errno != EINTR && errno != EAGAIN)
        sock_turn_off(server_sock);
    return sock_nonblocking(fd);
}

NETSock sock_connect(NETAddress address) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    NETSock sock = sock_nonblocking(fd);
    struct sockaddr *sockaddr = address_sockaddr(address);
    if (connect(fd, sockaddr, sizeof(*sockaddr)) < 0 &&
        errno != EINTR && errno != EINPROGRESS)
        sock_turn_off(sock);
    free(sockaddr);
    return sock;
}

void sock_release(NETSock sock) {
    sock_turn_off(sock);
    free(sock);
}

int sock_get_fd(NETSock sock) {
    return sock->fd;
}

void sock_set_fd(NETSock sock, int fd) {
    sock->fd = fd;
}

int sock_get_on(NETSock sock) {
    return sock->on;
}

void sock_set_on(NETSock sock, int on) {
    sock->on = on;
}

int sock_fd_is(NETSock sock, int fd) {
    return (sock->fd == fd) ? 1 : 0;
}

int sock_is_on(NETSock sock) {
    return sock->on;
}

int sock_is_off(NETSock sock) {
    return (sock->on) ? 0 : 1;
}

void sock_turn_off(NETSock sock) {
    close(sock->fd);
    sock->fd = -1;
    sock->on = 0;
}

int sock_send(NETSock sock, char *text) {
    int nbytes = strlen(text);
    #ifdef __APPLE__
    int status = send(sock->fd, text, nbytes, 0);
    #else
    int status = send(sock->fd, text, nbytes, MSG_NOSIGNAL);
    #endif
    if (status == nbytes)
        return 1;
    else if (status < 0 && errno != EINTR && errno != EAGAIN)
        sock_turn_off(sock);
    return 0;
}

char *sock_recv(NETSock sock) {
    char buffer[1024];
    int nbytes = recv(sock->fd, buffer, sizeof(buffer), 0);
    if (nbytes > 0) {
        buffer[nbytes] = 0;
        return str_dup(buffer);
    }
    if (nbytes == 0 || (nbytes < 0 && errno != EINTR && errno != EAGAIN))
        sock_turn_off(sock);
    return NULL;
}

int sock_list_poll(NETSock socks[], int pollin[], int pollout[], int nfds, int timeout) {
    struct pollfd *fds = (struct pollfd *) memalloc(nfds * sizeof(struct pollfd));
    for (int i = 0; i < nfds; i++) {
        fds[i].fd = socks[i]->fd;
        fds[i].events = 0;
        fds[i].events |= (pollin[i]) ? POLLIN : 0;
        fds[i].events |= (pollout[i]) ? POLLOUT : 0;
    }
    int result = poll(fds, nfds, timeout);
    for (int i = 0; i < nfds; i++) {
        if (fds[i].revents & POLLERR || fds[i].revents & POLLHUP ||
            fds[i].revents & POLLNVAL)
            sock_turn_off(socks[i]);
    }
    free(fds);
    return result;
}

