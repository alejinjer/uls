#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    char *ptr = dst;

    while ((len--) && *src)
        *dst++ = *src++;
    while (len-- + 1)
        *dst++ = '\0';
    return ptr;
}
