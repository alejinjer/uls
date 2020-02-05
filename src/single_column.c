#include "uls.h"

static void print_line(t_file *file, int *size, int flags) {
    time_t *t = &(file->st_mtimespec.tv_sec);

    (flags & LS_UU) ? t = &(file->st_btimespec.tv_sec) : 0;
    (flags & LS_C) ? t = &(file->st_ctimespec.tv_sec) : 0;
    (flags & LS_U) ? t = &(file->st_atimespec.tv_sec) : 0;
    mx_print_chmod(file, 1);
    mx_print_nlinks(file, size[0], flags);
    !(flags & LS_G) ? mx_print_uid(file, size[1]) : (void)0;
    !(flags & LS_O) ? mx_print_gid(file, size[2]) : (void)0;
    if (MX_ISCHR(file->st_mode) || MX_ISBLK(file->st_mode)) {
        mx_print_major(file, 3);
        mx_print_minor(file, 3);
    }
    else
        mx_print_size(file, size[3], flags);
    mx_print_time(t);
    mx_print_name(file, flags);
    MX_ISLNK(file->st_mode) ? mx_print_link(file) : (void)0;
    mx_printstr("\n");
}

static void ls_m(t_file *list, int flags) {
    static int counter = 0;
    int win_size = mx_terminal_size(flags);

    mx_print_name(list, flags);
    counter = (list->next ? (counter + mx_strlen(list->name) + 2) : 0);
    if (list->next) {
        mx_printstr(", ");
        if (!list->next->next) {
            if (counter + mx_strlen(list->next->name) >= win_size) {
                mx_printchar('\n');
                counter = 0;
            }
        }
        else if (counter + mx_strlen(list->next->name) + 2 >= win_size) {
            mx_printchar('\n');
            counter = 0;
        }
    }
    else
        mx_printchar('\n');
}

void mx_output(t_file *list, int flags) {
    int *size = (flags & LS_L) ? mx_get_row_size(list) : NULL;
    
    while (list) {
        if (flags & LS_L)
            print_line(list, size, flags);
        else if (flags & LS_M)
            ls_m(list, flags);
        else {
            mx_printstr(list->name);
            mx_printstr("\n");
        }
        list = list->next;
    }
    free(size);
}
