#include <glib.h>
#include <stdlib.h>

#include "util/mem/mem.h"

static void test_memalloc_1() {
    void *p = memalloc(32);
    g_assert(p != NULL);
    free(p);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/mem/memalloc", test_memalloc_1);
    return g_test_run();
}

