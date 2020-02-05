#include "uls.h"

static void print_files(t_file *list, int flags) {
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
        print_files(list, flags);
        while (ptr) {
            (MX_ISDIR(ptr->st_mode) && mx_strcmp(ptr->name, ".")
                && mx_strcmp(ptr->name, ".."))
                ? print_dirs_recur(ptr, flags)
                : (void)0;
            ptr = ptr->next;
        }
    }
}

static void print_dirs(t_file *list, int flags) {
    t_file *ptr = list;

    while (ptr) {
        if (list->next) {
            mx_printstr(ptr->name);
            mx_printstr(":\n");
        }
        print_files(ptr, flags);
        if ((flags & LS_RR)) {
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

void mx_print_all(t_list *errs, t_file *files, t_file *dirs, int flags) {
    errs ? mx_err_output(errs) : (void)0;
    files ? print_files(files, flags) : (void)0;
    (files && dirs) ? mx_printchar('\n') : (void)0;
    if (dirs) {
        ((errs || files) && !dirs->next)
            ? mx_printstr(dirs->name),
            mx_printstr(":\n") : (void)0;
    }
    dirs ? print_dirs(dirs, flags) : (void)0;
}
