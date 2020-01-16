#include "uls.h"

static void process_dirs(int argc, char *argv[], int flags, t_file **dirs);
static void process_other(int argc, char *argv[], t_list **e, t_file **f);

int main(int argc, char *argv[]) {
    // parse flags
    /*...*/
    int flags_count;
    int flags;
    t_file *directories = NULL;
    t_file *files = NULL;
    t_list *errors = NULL;

    if ((flags_count = mx_parse_flags(argc, argv, &flags)) == -1)
        return (1);
    /*...*/

    // parse args and add them to list
    /*...*/
    argv += flags_count;
    argc -= flags_count;
    process_other(argc, argv, &errors, &files);
    process_dirs(argc, argv, flags, &directories);
    mx_sort_list(errors, mx_sort_errors);
    mx_lst_sort(&files, mx_sort_by_name, flags);
    mx_lst_sort(&directories, mx_sort_by_name, flags);
    /*...*/

    // display all
    while (errors) {
        mx_printerr((char *)errors->data);
        errors = errors->next;
    }
    files ? mx_output(files, flags) : (void)0;
    mx_printstr("\n");
    directories ? mx_output(directories, flags) : (void)0;

    // system("leaks -q uls");
    return 0;
}

static void process_other(int argc, char *argv[], t_list **e, t_file **f) {
    for (int i = 0; i < argc; i++)
        mx_handle_nonexistent(argv[i], e, f);
}

static void process_dirs(int argc, char *argv[], int flags, t_file **dirs) {
    for (int i = 0; i < argc; i++)
        mx_explore_path(argv[i], flags, dirs);
}
