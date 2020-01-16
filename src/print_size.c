#include "uls.h"

void mx_print_size(t_file *file) {
    char *size = mx_lltoa(file->st_size);

    mx_printstr(size);
    mx_strdel(&size);
}
