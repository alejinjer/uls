#include "uls.h"

void mx_print_major(t_file *file, int nspaces) {
    int major = MX_MAJOR(file->st_rdev);

    mx_printnchar(' ', nspaces - mx_intlength(MX_MAJOR(file->st_rdev)));
    mx_printint(major);
    mx_printstr(", ");
}
