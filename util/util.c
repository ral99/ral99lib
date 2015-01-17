#include <stdlib.h>

#include "util/util.h"

void *memalloc(int size) {
    void *buffer = malloc(size);
    if (!buffer)
        exit(EXIT_FAILURE);
    return buffer;
}

