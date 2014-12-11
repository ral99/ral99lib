#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "net/address/address.h"
#include "util/util.h"
#include "adt/adt.h"

Address address_new(char *ip, int port) {
    Address address = memalloc(sizeof(*address));
    address->ip = str_dup(ip);
    address->port = port;
    return address;
}

void address_release(Address address) {
    free(address->ip);
    free(address);
}

int address_equals(Address address1, Address address2) {
    return (str_equals(address1->ip, address2->ip) &&
            address1->port == address2->port) ? 1 : 0;
}

char *address_to_str(Address address) {
    List address_list = list_new();
    list_append(address_list, str_dup(address->ip));
    list_append(address_list, int_to_str(address->port));
    char *str = list_to_str(address_list, (char *(*)(void *)) str_dup);
    list_full_release(address_list, free);
    return str;
}

Address address_from_str(char *str) {
    List address_list = list_from_str(str, (void *(*)(char *)) str_dup);
    char *ip = list_at(address_list, 0);
    int port = int_from_str(list_at(address_list, 1));
    Address address = address_new(ip, port);
    list_full_release(address_list, free);
    return address;
}

Address address_dup(Address address) {
    return address_new(address->ip, address->port);
}

char *address_get_ip(Address address) {
    return address->ip;
}

void address_set_ip(Address address, char *ip) {
    address->ip = ip;
}

int address_get_port(Address address) {
    return address->port;
}

void address_set_port(Address address, int port) {
    address->port = port;
}

int address_ip_is(Address address, char *ip) {
    return str_equals(address->ip, ip);
}

int address_port_is(Address address, int port) {
    return (address->port == port) ? 1 : 0;
}

char *address_ip(Address address) {
    return str_dup(address->ip);
}

int address_port(Address address) {
    return address->port;
}

struct sockaddr *address_sockaddr(Address address) {
    struct sockaddr_in *sockaddr = memalloc(sizeof(*sockaddr));
    memset(sockaddr, 0, sizeof(*sockaddr));
    sockaddr->sin_family = AF_INET;
    sockaddr->sin_addr.s_addr = inet_addr(address->ip);
    sockaddr->sin_port = htons(address->port);
    return (struct sockaddr *) sockaddr;
}

