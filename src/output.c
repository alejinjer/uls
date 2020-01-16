#include "uls.h"

// тестовый вывод, нужно написать нормальный
void mx_output(t_file *list, int flags) {
    char chmod[12];
    int *size = mx_get_row_size(list);
    t_group *gr = NULL;

    if (flags & LS_L) {
        mx_print_total_nblocks(list);
        mx_printstr("\n");
    }
    while (list) {
        if (flags & LS_L) {
            gr = getgrgid(list->st_gid);
            mx_print_chmod(chmod, list);
            mx_printnchar(' ', size[1] - mx_intlength(list->st_nlink) + 1);
            mx_printint(list->st_nlink);
            mx_printchar(' ');
            mx_print_uid(list);
            mx_printnchar(' ', size[2] - mx_strlen(getpwuid(list->st_uid)->pw_name) + 2);
            mx_print_gid(list);
            (gr) ? mx_printnchar(' ', size[3] - mx_strlen(gr->gr_name) + 1) :
                mx_printnchar(' ', size[3] - mx_intlength(list->st_gid) + 1);
            if (chmod[0] != 'c' && chmod [0] != 'b') {
                mx_printnchar(' ', (size[4] + 1) - mx_intlength(list->st_size));
                mx_print_size(list);
            }
            else {
                mx_printnchar(' ', (size[5] + 1) - mx_intlength(major(list->st_rdev)));
                mx_print_major(list);
                mx_printchar(',');
                mx_printnchar(' ', (size[6] + 1) - mx_intlength(minor(list->st_rdev)));
                mx_print_minor(list);
            }
            mx_printchar(' ');
            mx_print_time(list);
            mx_printchar(' ');
        }
        mx_printstr(list->name);
        if (MX_ISLNK(list->st_mode)) {
            mx_printstr(" -> ");
            mx_printstr(list->symlink);
        }
        mx_printstr("\n");
        if (MX_ISDIR(list->st_mode) && list->subdirs && (flags & LS_RR) && mx_strcmp(list->name, "..") != 0 && strcmp(list->name, ".") != 0)
            mx_output(list->subdirs, flags);
        list = list->next;
    }
}
