#include "libmx.h"

static char *get_leaving(size_t buf_size, char delim, const int fd) {
    char *tmp = NULL;
    char *result_str = NULL;
    char buffer[buf_size + 1];
    int read_result = 0;
    int delim_index;

    while ((read_result = read(fd, buffer, buf_size)) > 0) {
        buffer[read_result] = '\0';
        tmp = mx_strjoin(result_str, buffer);
        mx_strdel(&result_str);
        result_str = mx_strdup(tmp);
        mx_strdel(&tmp);
        delim_index = mx_get_char_index(result_str, delim);
        if (delim_index >= 0)
            break;
    }
    return result_str;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *leavings[4096];
    char *last_leaving;
    char *tmp;
    int delim_index;

    if (fd < 0 || fd > 4096 || buf_size == 0 || read(fd, 0, 0) < 0)
        return -2;
    last_leaving = get_leaving(buf_size, delim, fd);
    tmp = mx_strjoin(leavings[fd], last_leaving);
    mx_strdel(&last_leaving);
    delim_index = mx_get_char_index(tmp, delim);
    if (delim_index == -2)
        return 0;
    delim_index >= 0 ? tmp[delim_index] = '\0' : 0;
    mx_strdel(&leavings[fd]);
    delim_index >= 0 ? leavings[fd] = mx_strdup(tmp + delim_index + 1) : 0;
    *lineptr = mx_strdup(tmp);
    mx_strdel(&tmp);
    return leavings[fd] ? mx_strlen(*lineptr) : -1;
}
