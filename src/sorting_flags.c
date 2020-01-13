#include "uls.h"

bool mx_sort_by_name(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (mx_strcmp(f1->name, f2->name) > 0 ? 1 : 0);
    return (mx_strcmp(f1->name, f2->name) > 0 ? 0 : 1);
}

// -S
bool mx_sort_by_size(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_size >= f2->st_size) ? 0 : 1;
    return (f1->st_size > f2->st_size) ? 1 : 0;
}

// -t
bool mx_sort_by_mtime(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_mtim >= f2->st_mtim) ? 0 : 1;
    return (f1->st_mtim > f2->st_mtim) ? 1 : 0;
}

void mx_sort_by(t_file **list, int flags, char sort) {
    mx_lst_sort(list, mx_sort_by_name, flags);
    switch (sort) {
        case 'S':
            mx_lst_sort(list, mx_sort_by_size, flags);
            break;
        case 't':
            mx_lst_sort(list, mx_sort_by_mtime, flags);
            break;
    }
}
