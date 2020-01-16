#include "uls.h"

void mx_print_minor(t_file *file) {
    mx_printint(minor(file->st_rdev));
}
