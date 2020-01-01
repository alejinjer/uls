#include "libmx.h"

char *mx_strdup(const char *s1) {
    char *duplicate = mx_strnew(mx_strlen(s1));

    if (duplicate == NULL)
        return NULL;
    return mx_strcpy(duplicate, s1);
}
