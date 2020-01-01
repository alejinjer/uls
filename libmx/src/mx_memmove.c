#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *pd = (unsigned char *)dst;
    const unsigned char *ps = (unsigned char *)src;

    if (ps < pd)
        for (pd += len, ps += len; len--;)
            *--pd = *--ps;
    else
        while (len--)
            *pd++ = *ps++;
    return dst;
}
