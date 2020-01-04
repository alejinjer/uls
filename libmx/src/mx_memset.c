#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char *ptr = b;

    while (len--)
        *ptr++ = c;
    return b;
}
