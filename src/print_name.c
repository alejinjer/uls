#include "uls.h"

void mx_print_name(t_file *file, int flags) {
    char *joined = mx_strjoin(file->name, "/");

    if ((flags & LS_P) && MX_ISDIR(file->st_mode)) {
        mx_printstr(joined);
        mx_strdel(&joined);
        return;
    }
    mx_printstr(file->name);
}
