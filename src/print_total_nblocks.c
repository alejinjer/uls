#include "uls.h"

void mx_print_total_nblocks(t_file *list) {
    int total = 0;
    char *total_str = NULL;
    t_file *ptr = list;

    while (ptr) {
        total += ptr->st_blocks;
        ptr = ptr->next;
    }
    mx_printstr("total ");
    total_str = mx_itoa(total);
    mx_printstr(total_str);
    mx_printchar('\n');
    mx_strdel(&total_str);
}
