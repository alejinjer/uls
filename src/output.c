#include "uls.h"

static void print_line(t_file *file, int *size, int flags) {
    time_t *t = &(file->st_mtimespec.tv_sec);

    (flags & LS_UU) ? t = &(file->st_btimespec.tv_sec) : 0;
    (flags & LS_C) ? t = &(file->st_ctimespec.tv_sec) : 0;
    (flags & LS_U) ? t = &(file->st_atimespec.tv_sec) : 0;
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
    mx_print_time(t);
    mx_printstr(file->name);
    MX_ISLNK(file->st_mode) ? mx_print_link(file) : (void)0;
    mx_printstr("\n");
}

void mx_output(t_file *list, int flags) {
    int *size; 

    if ((flags & LS_L) && MX_ISDIR(list->st_mode)) {
        mx_print_total_nblocks(list);
    }
    list = list->subdirs;
    size = mx_get_row_size(list);
    while (list) {
        if ((flags & LS_ONE) || !isatty(1))  
            mx_printstr(mx_strcat(list->name, "\n"));
        else if (flags & LS_L) {
            print_line(list, size, flags);
        } else {
            mx_output_multicolumn(list);
            return;
        }
        list = list->next;
    }
    free(size);
}
