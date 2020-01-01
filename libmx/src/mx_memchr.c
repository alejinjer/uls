#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *ptr = s;

    while (ptr && n--) {
        if (*ptr == c)
            return (void *)ptr;
        ptr++;
    }
    return NULL;
}
