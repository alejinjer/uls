#include "libmx.h"

char *mx_strnew(const int size) {
    char *buffer = NULL;

    if (size > 2147483646 || size < 0)
        return NULL;
    buffer = (char *)malloc(size + 1);
    if (buffer == NULL)
        return NULL;
    for (int i = 0; i <= size; i++) {
        buffer[i] = '\0';
    }
    return buffer;
}
