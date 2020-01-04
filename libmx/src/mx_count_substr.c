#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int count = 0;
    size_t sub_len = 0;
    size_t str_len = 0;

    if (!str || !sub)
        return -1;
    if (str_len < sub_len)
        return -1;
    if (mx_strcmp(sub, "") == 0)
        return 0;
    sub_len = mx_strlen(sub);
    str_len = mx_strlen(str);
    while (*str) {
        if (mx_strncmp(str, sub, sub_len) == 0)
            count++;
        str++;
    }
    return count;
}
