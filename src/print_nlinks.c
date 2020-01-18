#include "uls.h"

void mx_print_nlinks(t_file *file, int nspaces) {
    mx_printnchar(' ', nspaces - mx_intlength(file->st_nlink));
    mx_printint(file->st_nlink);
    mx_printchar(' ');
}
