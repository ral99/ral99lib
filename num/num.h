#ifndef __NUM__
#define __NUM__

#include <stdint.h>

#define TOL 1e-7

/* Return 1 if a is greater than b. 0, otherwise. */
int double_gt(double a, double b);

/* Return 1 if a is lower than b. 0, otherwise. */
int double_lt(double a, double b);

/* Return 1 if a is equal to b. 0, otherwise. */
int double_equals(double a, double b);

/* Return the string representation of double with the specified number of
 * decimal positions. */
char *double_to_str(double x, int decimal_positions);

/* Return the double from its string representation. */
double double_from_str(char *str);

/* Return the pointer cast of int. */
void *int_to_pointer(int x);

/* Return the int cast of pointer. */
int int_from_pointer(void *x);

/* Return a random integer in the range [start, end]. */
int int_random(int start, int end);

/* Return 1 if the number is prime. 0, otherwise. */
int int_is_prime(int x);

/* Return the greatest common divisor of a and b. */
int int_gcd(int a, int b);

/* Return the least common multiple of a and b. */
uint64_t uint64_lcm(int a, int b);

/* Return the string representation of int. */
char *int_to_str(int x);

/* Return the int from its string representation. */
int int_from_str(char *str);

#endif

