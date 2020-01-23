#include "uls.h"

static void print_line(t_file *file, int *size, int flags) {
    if (flags & LS_L) {
        mx_print_chmod(file, 1);
        mx_print_nlinks(file, size[0]);
        mx_print_uid(file, size[1]);
        mx_print_gid(file, size[2]);
        if (MX_ISCHR(file->st_mode) || MX_ISBLK(file->st_mode)) {
            mx_print_major(file, 3);
            mx_print_minor(file, 3);
        }
        else
            mx_print_size(file, size[3]);
        mx_print_time(file);
    }
    mx_printstr(file->name);
    MX_ISLNK(file->st_mode) ? mx_print_link(file) : (void)0;
    mx_printstr("\n");
}

void mx_output(t_file *list, int flags) {
    int *size = mx_get_row_size(list);

    if ((flags & LS_L) && MX_ISDIR(list->st_mode)) {
        mx_print_total_nblocks(list);
    }
    while (list) {
        if (flags & LS_L) {
            print_line(list, size, flags);
        } else {
            mx_printstr(list->name);
            mx_printstr("\n");
        }
        list = list->next;
    }
    free(size);
}
