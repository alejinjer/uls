#include "uls.h"

void mx_choose_output(t_file *list, int flags) {
    if ((flags & LS_L) || (flags & LS_ONE) || (flags & LS_M))
        mx_output(list, flags);
    else
        mx_output_multicolumn(list->subdirs, flags);
}
void mx_print_dirs(t_file *list, int flags, int lst_size) {
    t_file *ptr = list;

    while (ptr) {
        if (MX_ISDIR(ptr->st_mode)) {
            mx_choose_output(ptr, flags);
        }
        if (MX_ISDIR(ptr->st_mode) && ptr->subdirs && (flags & LS_RR)
            && mx_strcmp(ptr->subdirs->name, ".")
            && mx_strcmp(ptr->subdirs->name, ".."))
        {
            mx_printstr(ptr->full_path);
            mx_printstr(":\n");
            mx_print_dirs(ptr->subdirs, flags, lst_size);
        }
        ptr = ptr->next;
    }
}

void mx_choose_sort(t_file **list, int flags) {
    if (flags & LS_F)
        return;
    mx_lst_sort(list, mx_sort_by_name, flags);
    if (flags & LS_SS)
        mx_lst_sort(list, mx_sort_by_size, flags);
    // if (flags & LS_T) {
    //     if (flags & LS_UU)
    //         mx_lst_sort(list, mx_sort_by_btime, flags);
    //     else if (flags & LS_C)
    //         mx_lst_sort(list, mx_sort_by_ctime, flags);
    //     else if (flags & LS_U)
    //         mx_lst_sort(list, mx_sort_by_atime, flags);
    //     else
    //         mx_lst_sort(list, mx_sort_by_mtime, flags);
    // }
}

static void sort_all(t_file **list, int flags) {
    t_file *ptr;

    mx_choose_sort(list, flags);
    ptr = *list;
    while (ptr) {
        mx_choose_sort(&ptr->subdirs, flags);
        if ((flags & LS_RR) && ptr->subdirs) {
            sort_all(&ptr->subdirs, flags);
        }
        ptr = ptr->next;
    }
}

int main(int argc, char *argv[]) {
    int flags;
    int flags_count = mx_parse_flags(argc, argv, &flags);
    t_file *files = NULL;
    t_file *dirs = NULL;
    t_list *errs = mx_process_args((argv + flags_count), &files, &dirs, flags);

    errs ? mx_sort_list(errs, mx_sort_errors) : 0;
    errs ? mx_err_output(errs) : (void)0;
    files ? mx_choose_sort(&files, flags) : (void)0;
    files ? mx_choose_output(files, flags) : (void)0;
    dirs ? sort_all(&dirs, flags) : (void)0;
    dirs ? mx_print_dirs(dirs, flags, mx_lst_size(dirs)) : (void)0;
    // system("leaks -q uls");
    return 0;
}
