#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    int index = 0;
    int result_len;
    char *result;
    char *tmp;
    int sub_len;

    if (!str || !sub || !replace)
        return NULL;
    result_len = mx_strlen(str) - (mx_count_substr(str, sub) *
                                   (mx_strlen(sub) - mx_strlen(replace)));
    result = mx_strnew(result_len);
    sub_len = mx_strlen(sub);
    while ((index = mx_get_substr_index(str, sub)) != -1) {
        tmp = mx_strndup(str, index);
        result = mx_strcat(result, tmp);
        result = mx_strcat(result, replace);
        mx_strdel(&tmp);
        str += sub_len + index;
    }
    result = mx_strcat(result, str);
    return result;
}
