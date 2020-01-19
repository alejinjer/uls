#include "uls.h"

void mx_output(t_file *list, int flags) {
    int *size = mx_get_row_size(list);
    int max_length = mx_list_max(list);

    if (flags & LS_L && MX_ISDIR(list->st_mode)) {
        mx_print_total_nblocks(list);
        mx_printstr("\n");
    }
    while (list) {
        if (flags & LS_L) {
            mx_print_chmod(list, size[0]);
            mx_print_nlinks(list, size[1]);
            mx_print_uid(list, size[2]);
            mx_print_gid(list, size[3]);
            MX_ISCHR(list->st_mode) || MX_ISBLK(list->st_mode) 
                ? (mx_print_major(list, size[5]), mx_print_minor(list, size[6]))
                : mx_print_size(list, size[4]);
            mx_print_time(list);
        }
        mx_printstr(list->name);
        MX_ISLNK(list->st_mode) ? mx_print_link(list) : (void)0;
        if ((flags & LS_ONE) || (flags & LS_L))
            mx_printchar('\n');
        else {
            mx_printnchar(' ', max_length - mx_strlen(list->name));
            list->next ? mx_printchar('\t') : mx_printchar('\n');
        }
        if (MX_ISDIR(list->st_mode) && list->subdirs && (flags & LS_RR) 
            && mx_strcmp(list->name, "..") != 0 
            && mx_strcmp(list->name, ".") != 0)
            mx_output(list->subdirs, flags);
        list = list->next;
    }
    free(size);
}
