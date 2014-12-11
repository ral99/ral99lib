#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/int/int.h"
#include "util/mem/mem.h"

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

