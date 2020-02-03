#include "uls.h"

void mx_print_nlinks(t_file *file, int nspaces, int flags) {
    mx_printnchar(' ', nspaces - mx_intlength(file->st_nlink));
    mx_printint(file->st_nlink);
    if ((flags & LS_O) && (flags & LS_G))
        mx_printnchar(' ', 3);
    else
        mx_printchar(' ');
}
