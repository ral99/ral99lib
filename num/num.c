#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "num/num.h"
#include "util/util.h"

int double_gt(double a, double b) {
    return (a - b > TOL) ? 1 : 0;
}

int double_lt(double a, double b) {
    return (b - a > TOL) ? 1 : 0;
}

int double_equals(double a, double b) {
    return (double_gt(a, b) == 0 && double_gt(b, a) == 0) ? 1 : 0;
}

char *double_to_str(double x, int decimal_positions) {
    char format[8];
    char buf[32];
    sprintf(format, "%%.%dlf", decimal_positions);
    sprintf(buf, format, x);
    return strcpy(memalloc(strlen(buf) + 1), buf);
}

double double_from_str(char *str) {
    double x;
    sscanf(str, "%lf", &x);
    return x;
}

void *int_to_pointer(int x) {
    return (void *) ((long) x);
}

int int_from_pointer(void *x) {
    return (int) ((long) x);
}

int int_random(int start, int end) {
    return (rand() % (end - start + 1) + start);
}

char *int_to_str(int x) {
    char buf[32];
    sprintf(buf, "%d", x);
    return strcpy(memalloc(strlen(buf) + 1), buf);
}

int int_from_str(char *str) {
    int x;
    sscanf(str, "%d", &x);
    return x;
}

