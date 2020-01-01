#include "libmx.h"

bool mx_isnumber(char *s) {
    int i = -1;

    if (s[0] == '\0')
        return false;
    while (s[++i])
        if (!mx_isdigit(s[i]))
            return false;
    return true;
}
