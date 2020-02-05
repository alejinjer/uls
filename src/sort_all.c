#include "uls.h"

static void sort_files(t_file **list, int flags) {
    if (flags & LS_SS)
        mx_lst_sort(list, mx_sort_by_size, flags);
    else if (flags & LS_T) {
        if (flags & LS_UU)
            mx_lst_sort(list, mx_sort_by_btime, flags);
        else if (flags & LS_C)
            mx_lst_sort(list, mx_sort_by_ctime, flags);
        else if (flags & LS_U)
            mx_lst_sort(list, mx_sort_by_atime, flags);
        else
            mx_lst_sort(list, mx_sort_by_mtime, flags);
    }
    else
        mx_lst_sort(list, mx_sort_by_name, flags);
}

static void sort_dirs(t_file **list, int flags) {
    t_file *ptr;

    sort_files(list, flags);
    ptr = *list;
    while (ptr) {
        sort_files(&ptr->subdirs, flags);
        if ((flags & LS_RR) && ptr->subdirs)
            sort_dirs(&ptr->subdirs, flags);
        ptr = ptr->next;
    }
}

void mx_sort_all(t_list **errs, t_file **files, t_file **dirs, int flags) {
    errs ? mx_sort_list(*errs, mx_sort_errors) : 0;
    files ? sort_files(files, flags) : (void)0;
    dirs ? sort_dirs(dirs, flags) : (void)0;
}
