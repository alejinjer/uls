#include "libmx.h"

char *mx_strtrim(const char *str) {
    char *trimmed = NULL;
    int str_len;
    int trimmed_len = 0;
    int before = 0;
    int after = 0;

    if (!str)
        return NULL;
    str_len = mx_strlen(str);
    for (int i = 0; mx_isspace(str[i]); i++)
        before++;
    for (int i = str_len - 1; mx_isspace(str[i]); i--)
        after++;
    trimmed_len = str_len - before - after;
    if (trimmed_len < 0)
        return mx_strdup("");
    trimmed = mx_strnew(trimmed_len);
    trimmed = mx_strncpy(trimmed, str + before, trimmed_len);
    return trimmed;
}
