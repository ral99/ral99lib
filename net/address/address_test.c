#include <glib.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "net/address/address.h"
#include "adt/adt.h"

static void test_address_new_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpstr(address->ip, ==, "127.0.0.1");
    g_assert_cmpint(address->port, ==, 8000);
    address_release(address);
}

static void test_address_release_1() {
    Address address = address_new("127.0.0.1", 8000);
    address_release(address);
}

static void test_address_equals_1() {
    Address address1 = address_new("127.0.0.1", 8000);
    Address address2 = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_equals(address1, address2), ==, 1);
    address_release(address1);
    address_release(address2);
}

static void test_address_equals_2() {
    Address address1 = address_new("127.0.0.1", 8000);
    Address address2 = address_new("127.0.0.1", 8001);
    g_assert_cmpint(address_equals(address1, address2), ==, 0);
    address_release(address1);
    address_release(address2);
}

static void test_address_equals_3() {
    Address address1 = address_new("127.0.0.1", 8000);
    Address address2 = address_new("127.0.0.0", 8000);
    g_assert_cmpint(address_equals(address1, address2), ==, 0);
    address_release(address1);
    address_release(address2);
}

static void test_address_equals_4() {
    Address address1 = address_new("127.0.0.1", 8000);
    Address address2 = address_new("127.0.0.0", 8001);
    g_assert_cmpint(address_equals(address1, address2), ==, 0);
    address_release(address1);
    address_release(address2);
}

static void test_address_to_str_1() {
    Address address = address_new("127.0.0.1", 8000);
    char *str = address_to_str(address);
    g_assert_cmpstr(str, ==, "127.0.0.1,8000");
    free(str);
    address_release(address);
}

static void test_address_from_str_1() {
    Address address1 = address_from_str("127.0.0.1,8000");
    Address address2 = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_equals(address1, address2), ==, 1);
    address_release(address1);
    address_release(address2);
}

static void test_address_dup_1() {
    Address address = address_new("127.0.0.1", 8000);
    Address dup = address_dup(address);
    g_assert_cmpint(address_equals(address, dup), ==, 1);
    address_release(address);
    address_release(dup);
}

static void test_address_get_ip_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert(address_get_ip(address) == address->ip);
    address_release(address);
}

static void test_address_set_ip_1() {
    Address address = address_new("127.0.0.1", 8000);
    char *ip = str_dup("127.0.0.1");
    free(address->ip);
    address_set_ip(address, ip);
    g_assert(address->ip == ip);
    address_release(address);
}

static void test_address_get_port_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_get_port(address), ==, address->port);
    address_release(address);
}

static void test_address_set_port_1() {
    Address address = address_new("127.0.0.1", 8000);
    int port = 8001;
    address_set_port(address, port);
    g_assert_cmpint(address->port, ==, port);
    address_release(address);
}

static void test_address_ip_is_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_ip_is(address, "127.0.0.1"), ==, 1);
    address_release(address);
}

static void test_address_ip_is_2() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_ip_is(address, "127.0.0.0"), ==, 0);
    address_release(address);
}

static void test_address_port_is_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_port_is(address, 8000), ==, 1);
    address_release(address);
}

static void test_address_port_is_2() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_port_is(address, 8001), ==, 0);
    address_release(address);
}

static void test_address_ip_1() {
    Address address = address_new("127.0.0.1", 8000);
    char *ip = address_ip(address);
    g_assert_cmpstr(ip, ==, "127.0.0.1");
    free(ip);
    address_release(address);
}

static void test_address_port_1() {
    Address address = address_new("127.0.0.1", 8000);
    g_assert_cmpint(address_port(address), ==, 8000);
    address_release(address);
}

static void test_address_sockaddr_1() {
    Address address = address_new("127.0.0.1", 8000);
    struct sockaddr *sockaddr = address_sockaddr(address);
    g_assert(sockaddr != NULL);
    g_assert_cmpint(sockaddr->sa_family, ==, AF_INET);
    free(sockaddr);
    address_release(address);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/address/new", test_address_new_1);
    g_test_add_func("/address/release", test_address_release_1);
    g_test_add_func("/address/equals", test_address_equals_1);
    g_test_add_func("/address/equals", test_address_equals_2);
    g_test_add_func("/address/equals", test_address_equals_3);
    g_test_add_func("/address/equals", test_address_equals_4);
    g_test_add_func("/address/to_str", test_address_to_str_1);
    g_test_add_func("/address/from_str", test_address_from_str_1);
    g_test_add_func("/address/dup", test_address_dup_1);
    g_test_add_func("/address/get_ip", test_address_get_ip_1);
    g_test_add_func("/address/set_ip", test_address_set_ip_1);
    g_test_add_func("/address/get_port", test_address_get_port_1);
    g_test_add_func("/address/set_port", test_address_set_port_1);
    g_test_add_func("/address/ip_is", test_address_ip_is_1);
    g_test_add_func("/address/ip_is", test_address_ip_is_2);
    g_test_add_func("/address/port_is", test_address_port_is_1);
    g_test_add_func("/address/port_is", test_address_port_is_2);
    g_test_add_func("/address/ip", test_address_ip_1);
    g_test_add_func("/address/port", test_address_port_1);
    g_test_add_func("/address/sockaddr", test_address_sockaddr_1);
    return g_test_run();
}

