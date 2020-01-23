#include "uls.h"

void mx_print_total_nblocks(t_file *list) {
    int total = 0;
    char *total_str = NULL;
    t_file *ptr = list;
    t_file *recur_ptr = NULL;

    while (ptr) {
        total += ptr->st_blocks;
        if (ptr->subdirs) {
            recur_ptr = ptr->subdirs;
            while (recur_ptr) {
                total += recur_ptr->st_blocks;
                recur_ptr = recur_ptr->next;
            }
        }
        ptr = ptr->next;
    }
    mx_printstr("total ");
    total_str = mx_itoa(total);
    mx_printstr(total_str);
    mx_printchar('\n');
    mx_strdel(&total_str);
}
