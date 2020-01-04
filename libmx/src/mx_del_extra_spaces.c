#include "libmx.h"

static int get_final_len(char *trimmed_str) {
    int final_str_len = mx_strlen(trimmed_str);

    for (int i = 0; i < mx_strlen(trimmed_str) - 1; i++)
        if (mx_isspace(trimmed_str[i]) && mx_isspace(trimmed_str[i + 1]))
            final_str_len--;
    return final_str_len;
}

char *mx_del_extra_spaces(const char *str) {
    char *trimmed_str = NULL;
    char *final_str = NULL;
    int final_str_len = 0;
    int j = 0;

    if (!(trimmed_str = mx_strtrim(str)))
        return NULL;
    final_str_len = get_final_len(trimmed_str);
    final_str = mx_strnew(final_str_len);
    for (int i = 0; i < mx_strlen(trimmed_str); i++) {
        if (mx_isspace(trimmed_str[i]) && mx_isspace(trimmed_str[i + 1]))
            continue;
        else if (mx_isspace(trimmed_str[i]))
            final_str[j] = ' ';
        else
            final_str[j] = trimmed_str[i];
        j++;
    }
    mx_strdel(&trimmed_str);
    return final_str;
}
