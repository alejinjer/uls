#include "uls.h"

void mx_print_gid(t_file *file, int nspaces) {
    t_group *group = getgrgid(file->st_gid);
    int len;

    group ? mx_printstr(group->gr_name) : mx_printint(file->st_gid);
    len = group ? mx_strlen(group->gr_name) : mx_intlength(file->st_gid);
    mx_printnchar(' ', nspaces - len + 2);
}
