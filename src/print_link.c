#include "uls.h"

void mx_print_link(t_file *file) {
    mx_printstr(" -> ");
    mx_printstr(file->symlink);
}
