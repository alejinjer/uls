#include "uls.h"

void mx_print_dirs(t_file *list, int flags);

void mx_print_files(t_file *list, int flags) {
    if (!list)
        return;
    if (MX_ISDIR(list->st_mode)) {
        if (!list->subdirs)
            return;
        list = list->subdirs;
        if (list->error) {
            mx_printerr(list->error);
            return;
        }
        (flags & LS_L) ? mx_print_total_nblocks(list) : (void)0;
    }
    ((flags & LS_L) || (flags & LS_ONE) || (flags & LS_M))
        ? mx_output(list, flags)
        : mx_output_multicolumn(list, flags);
}

static void print_dirs_recur(t_file *list, int flags) {
    t_file *ptr = list->subdirs;

    if (mx_strcmp(list->name, ".") && mx_strcmp(list->name, "..")) {
        mx_printstr("\n");
        mx_printstr(list->full_path);
        mx_printstr(":\n");
        mx_print_files(list, flags);
        while (ptr) {
            (MX_ISDIR(ptr->st_mode) && mx_strcmp(ptr->name, ".")
                && mx_strcmp(ptr->name, ".."))
                ? print_dirs_recur(ptr, flags) : (void)0;
            ptr = ptr->next;
        }
    }
}

void mx_print_dirs(t_file *list, int flags) {
    t_file *ptr = list;

    while (ptr) {
        if (list->next) {
            mx_printstr(ptr->name);
            mx_printstr(":\n");
        }
        mx_print_files(ptr, flags);
        if ((flags & LS_RR))
        {
            t_file *sub_ptr = ptr->subdirs;

            while (sub_ptr) {
                if (MX_ISDIR(sub_ptr->st_mode))
                    print_dirs_recur(sub_ptr, flags);
                sub_ptr = sub_ptr->next;
            }
        }
        ptr->next ? mx_printchar('\n') : (void)0;
        ptr = ptr->next;
    }
}

void mx_choose_sort(t_file **list, int flags) {
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

    mx_choose_sort(list, flags);
    ptr = *list;
    while (ptr) {
        mx_choose_sort(&ptr->subdirs, flags);
        if ((flags & LS_RR) && ptr->subdirs)
            sort_dirs(&ptr->subdirs, flags);
        ptr = ptr->next;
    }
}

static void print_all(t_list *errs, t_file *files, t_file *dirs, int flags) {
    errs ? mx_err_output(errs) : (void)0;
    files ? mx_print_files(files, flags) : (void)0;
    (files && dirs) ? mx_printchar('\n') : (void)0;
    if (dirs) {
        ((errs || files) && !dirs->next)
            ? mx_printstr(dirs->name), mx_printstr(":\n") : (void)0;
    }
    dirs ? mx_print_dirs(dirs, flags) : (void)0;
}

int main(int argc, char *argv[]) {
    int flags;
    int flags_count = mx_parse_flags(argc, argv, &flags);
    t_file *files = NULL;
    t_file *dirs = NULL;
    t_list *errs = mx_process_args((argv + flags_count), &files, &dirs, flags);

    errs ? mx_sort_list(errs, mx_sort_errors) : 0;
    files ? mx_choose_sort(&files, flags) : (void)0;
    dirs ? sort_dirs(&dirs, flags) : (void)0;
    print_all(errs, files, dirs, flags);
    // system("leaks -q uls");
    return errs ? 1 : 0;
}
