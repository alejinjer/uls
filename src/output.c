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
    int i = (flags & LS_P) ? 3 : 2;

    mx_print_name(list, flags);
    list->next ? mx_printstr(", ") : (void)0;
    counter += mx_strlen(list->name);
    if ((flags & LS_P) && MX_ISDIR(list->st_mode))
        counter += 3;
    else 
        counter += 2;
    if (list->next) {
        if (counter + mx_strlen(list->next->name) > win_size - i - 1) {
            mx_printchar('\n');
            counter = 0;
        }
    }
    else {
        mx_printchar('\n');
        counter = 0;
    }
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
