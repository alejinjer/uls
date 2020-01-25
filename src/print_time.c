#include "uls.h"

void mx_print_time(time_t *t) {
    char *temp_time = ctime(t);
    char *result = mx_strnew(12);
    time_t now = time(NULL);
    long half_year = 15778463;

    if ((now - half_year) > *t
        || now < *t)
    {
        result = mx_strncpy(result, temp_time + 4, 6);
        mx_strcpy(result + 6, "  ");
        mx_strncpy(result + 8, temp_time + 20, 4);
    }
    else
        result = mx_strncpy(result, temp_time + 4, 12);
    mx_printstr(result);
    mx_printchar(' ');
    mx_strdel(&result);
}
