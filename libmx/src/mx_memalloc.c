#include "libmx.h"

void *mx_memalloc(size_t size) {
    size_t i;
    char *str;

    if ((str = (char *)malloc(size)) == NULL)
        return (NULL);
    i = -1;
    while (++i < size)
        str[i] = 0;
    return (str);
}
