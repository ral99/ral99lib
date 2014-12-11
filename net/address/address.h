#ifndef __NET__ADDRESS__
#define __NET__ADDRESS__

#include <netinet/in.h>

typedef struct Address *Address;
struct Address {
    char *ip;
    int port;
};

/* Return a new address. */
Address address_new(char *ip, int port);

/* Free the memory used by address. */
void address_release(Address address);

/* Return 1 if addresses are equal. 0, otherwise. */
int address_equals(Address address1, Address address2);

/* Return the string representation of the address. */
char *address_to_str(Address address);

/* Return address from its string representation. */
Address address_from_str(char *str);

/* Return the duplicated address. */
Address address_dup(Address address);

/* Getter method for ip. */
char *address_get_ip(Address address);

/* Setter method for ip. */
void address_set_ip(Address address, char *ip);

/* Getter method for port. */
int address_get_port(Address address);

/* Setter method for port. */
void address_set_port(Address address, int port);

/* Boolean method for ip. */
int address_ip_is(Address address, char *ip);

/* Boolean method for port. */
int address_port_is(Address address, int port);

/* Return the address ip. */
char *address_ip(Address address);

/* Return the address port. */
int address_port(Address address);

/* Return address sockaddr. */
struct sockaddr *address_sockaddr(Address address);

#endif

