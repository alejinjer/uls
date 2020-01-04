#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    const unsigned char *b = big;
    const unsigned char *l = little;

    if (big_len < little_len)
        return NULL;
    if (big_len == 0 || little_len == 0)
        return NULL;
    while (b && (big_len-- >= little_len)) {
        if ((mx_memcmp(b, l, little_len) == 0))
            return (void *)b;
        b++;
    }
    return NULL;
}
