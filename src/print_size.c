#include "uls.h"

void mx_print_size(t_file *file, int nspaces) {
    char *size = mx_lltoa(file->st_size);

    mx_printnchar(' ', nspaces - mx_longlong_length(file->st_size));
    mx_printstr(size);
    mx_printchar(' ');
    mx_strdel(&size);
}
