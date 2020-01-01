#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    for (int i = 0; i <= mx_strlen(s1); i++)
        if (!s1[i])
            for (int j = 0; j <= mx_strlen(s2); j++)
                s1[i++] = s2[j];
    return s1;
}
