#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;
    size_t i = -1;

    while (++i < n)
        if (p1[i] != p2[i])
            return p1[i] - p2[i];
    return 0;
}
