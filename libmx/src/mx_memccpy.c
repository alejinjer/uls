#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    size_t i = -1;

    while (++i < n) {
        d[i] = s[i];
        if (s[i] == c)
            return ((void *)(d + i + 1));
    }
    return NULL;
}
