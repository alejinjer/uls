#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *ptr = s;

    ptr += n;
    while (ptr && n--) {
        if (*ptr == c)
            return (void *)ptr;
        ptr--;
    }
    return NULL;
}
