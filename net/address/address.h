#ifndef __NET__ADDRESS__
#define __NET__ADDRESS__

#include <netinet/in.h>

typedef struct _NETAddress *NETAddress;
struct _NETAddress {
    char *ip;
    int port;
};

/* Return a new address. */
NETAddress address_new(char *ip, int port);

/* Free the memory used by address. */
void address_release(NETAddress address);

/* Return 1 if addresses are equal. 0, otherwise. */
int address_equals(NETAddress address1, NETAddress address2);

/* Return the string representation of the address. */
char *address_to_str(NETAddress address);

/* Return address from its string representation. */
NETAddress address_from_str(char *str);

/* Return the duplicated address. */
NETAddress address_dup(NETAddress address);

/* Getter method for ip. */
char *address_get_ip(NETAddress address);

/* Setter method for ip. */
void address_set_ip(NETAddress address, char *ip);

/* Getter method for port. */
int address_get_port(NETAddress address);

/* Setter method for port. */
void address_set_port(NETAddress address, int port);

/* Boolean method for ip. */
int address_ip_is(NETAddress address, char *ip);

/* Boolean method for port. */
int address_port_is(NETAddress address, int port);

/* Return the address ip. */
char *address_ip(NETAddress address);

/* Return the address port. */
int address_port(NETAddress address);

/* Return address sockaddr. */
struct sockaddr *address_sockaddr(NETAddress address);

#endif

