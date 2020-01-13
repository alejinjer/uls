#include "uls.h"

void mx_print_gid(t_file *file) {
    t_group *group = getgrgid(file->st_gid);

    group ? mx_printstr(group->gr_name) : mx_printint(file->st_gid);
}
