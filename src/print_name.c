#include "uls.h"

void mx_print_name(t_file *file, int flags) {
    if ((flags & LS_P) && MX_ISDIR(file->st_mode)) {
        char *joined = mx_strjoin(file->name, "/");

        mx_printstr(joined);
        mx_strdel(&joined);
        return;
    }
    mx_printstr(file->name);
}
