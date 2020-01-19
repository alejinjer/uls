#include "uls.h"

void mx_print_minor(t_file *file, int nspaces) {
    int minor = MX_MINOR(file->st_rdev);
    char *hex_minor = NULL;

    if (minor < 256) {
        mx_printnchar(' ', nspaces - mx_intlength(minor));
        mx_printint(minor);
    }
    else {
        hex_minor = mx_nbr_to_hex(minor);
        mx_printstr("0x");
        mx_printnchar('0', 8 - mx_strlen(hex_minor));
        mx_printstr(hex_minor);
        mx_strdel(&hex_minor);
    }
    mx_printchar(' ');
}
