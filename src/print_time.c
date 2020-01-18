#include "uls.h"

void mx_print_time(t_file *file) {
    char *s = ctime(&(file->st_mtim)) + 4;
    char *s1 = mx_strndup(s, 12);

    mx_printstr(s1);
    mx_printchar(' ');
    mx_strdel(&s1);
}
