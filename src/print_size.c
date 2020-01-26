#include "uls.h"

void mx_print_size(t_file *file, int nspaces, int flags) {
    char *size = NULL;
    char *hr_size = NULL;

    if (flags & LS_H) {
        hr_size = mx_hr_size(file->st_size);
        mx_printchar(' ');
        mx_printstr(hr_size);
        mx_strdel(&hr_size);
    }
    else {
        size = mx_lltoa(file->st_size);
        mx_printnchar(' ', nspaces - mx_longlong_length(file->st_size));
        mx_printstr(size);
        mx_strdel(&size);
    }
    mx_printchar(' ');
}
