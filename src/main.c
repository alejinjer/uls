#include "uls.h"

// static void sort_all(t_list **errs, t_file **files, t_file **dirs, int flags) {
//     t_file *dir_ptr;

//     mx_lst_sort(files, mx_sort_by_name, flags);
//     mx_lst_sort(dirs, mx_sort_by_name, flags);
//     dir_ptr = *dirs;
//     while (dir_ptr) {
//         if (dir_ptr->subdirs)
//             mx_lst_sort(&dir_ptr->subdirs, mx_sort_by_name, flags);
//         dir_ptr = dir_ptr->next;
//     }
// }

// static void print_all(t_list *errs, t_file *files, t_file *dirs, int flags)
// {
//     t_file *dir_ptr = dirs;

//     mx_err_output(errs);
//     files ? mx_output(files, flags) : (void)0;
//     dirs ? mx_output(dirs, flags) : (void)0;
//     if (dir_ptr && (flags & LS_RR)) {
//         while (dir_ptr) {
//             if (MX_ISDIR(dir_ptr->st_mode)) {
//                 printf("\n%s:\n", dir_ptr->full_path);
//                 mx_print_total_nblocks(dir_ptr);
//             }
//             print_all(NULL, NULL, dir_ptr->subdirs, flags);
//             dir_ptr = dir_ptr->next;
//         }
//     }
// }

void mx_print_dirs(t_file *list, int flags) {
    t_file *ptr = list;

    while (ptr) {
        if (MX_ISDIR(ptr->st_mode) && ptr->subdirs) {
            mx_output(ptr->subdirs, flags);
            if (MX_ISDIR(ptr->st_mode) && ptr->subdirs
                && mx_strcmp(ptr->subdirs->name, ".")
                && mx_strcmp(ptr->subdirs->name, "..")) 
            {
                mx_print_dirs(ptr->subdirs, flags);
            }
        }
        ptr = ptr->next;
    }
}

void mx_choose_output(char **argv, int flags, int flags_count, t_file *list) {
    if (!*(argv + flags_count)) {
        mx_print_dirs(list, flags);
        return;
    }
    for (int i = flags_count; i >= 0; i--) {
        for (int j = mx_strlen(argv[i]) - 1; j >= 0; j--) {
            if (argv[i][j] == 'C') {
                // multicolumn
                return;
            } else {
                if (!MX_ISDIR(list->st_mode)) {
                    mx_output(list, flags);
                    return;
                }
                mx_print_dirs(list, flags);
                return;
            }
        }
    }
}

void mx_choose_sort(char **argv, int flags, int flags_count, t_file **list) {
    !(flags & LS_F) ? mx_lst_sort(list, mx_sort_by_name, flags) : (void)0;
    if (flags & LS_SS && !(flags & LS_F)) {
        mx_lst_sort(list, mx_sort_by_size, flags);
        return;
    }
    if (flags & LS_T && !(flags & LS_F))
        for (int i = flags_count; i >= 0; i--)
            for (int j = mx_strlen(argv[i]) - 1; j >= 0; j--) {
                if (argv[i][j] == 'U') {
                    //
                    return;
                }
                if (argv[i][j] == 'c') {
                    //
                    return;
                }
                if (argv[i][j] == 'u') {
                    //
                    return;
                }
            }
}

static void sort_all(char **argv, int flags, int flags_count, t_file **list) {
    t_file *ptr = *list;

    while (ptr) {
        mx_choose_sort(argv, flags, flags_count, &ptr->subdirs);
        if ((flags & LS_RR) && ptr->subdirs) {
            sort_all(argv, flags, flags_count, &ptr->subdirs);
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
    files ? mx_choose_sort(argv, flags, flags_count, &files) : (void)0;
    files ? mx_choose_output(argv, flags, flags_count, files) : (void)0;
    dirs ? sort_all(argv, flags, flags_count, &dirs) : (void)0;
    dirs ? mx_choose_output(argv, flags, flags_count, dirs) : (void)0;
    // system("leaks -q uls");
    return 0;
}
