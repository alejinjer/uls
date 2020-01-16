#include "uls.h"

void mx_print_major(t_file *file) {
    mx_printint(major(file->st_rdev));
}
