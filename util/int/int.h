#ifndef __UTIL__INT__
#define __UTIL__INT__

/* Return the pointer cast of int. */
void *int_to_pointer(int x);

/* Return the int cast of pointer. */
int int_from_pointer(void *x);

/* Return a random integer in the range [start, end]. */
int int_random(int start, int end);

/* Return the string representation of int. */
char *int_to_str(int x);

/* Return the int from its string representation. */
int int_from_str(char *str);

#endif

