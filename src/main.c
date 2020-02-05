#include "uls.h"

int main(int argc, char *argv[]) {
    int flags;
    int flags_count = mx_parse_flags(argc, argv, &flags);
    t_file *files = NULL;
    t_file *dirs = NULL;
    t_list *errs = NULL;

    errs = mx_process_args((argv + flags_count), &files, &dirs, &flags);
    mx_sort_all(&errs, &files, &dirs, flags);
    mx_print_all(errs, files, dirs, flags);
    return errs ? 1 : (flags & ERROR) / ERROR;
}
