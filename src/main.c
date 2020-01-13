#include "uls.h"

static char get_last_sort_flag(int argc, char **argv) {
    int j;

    for (int i = argc; i >= 1; --i) {
        j = mx_strlen(argv[i]) - 1;
        for (; j >= 0; j--)
            if (argv[i][j] == 'S' || argv[i][j] == 't')
                return argv[i][j];
    }
    return '\0';
}

int main(int argc, char *argv[]) {
    // parse flags
    /*...*/
    int flags_count;
    int flags;
    char last_sort_flag;
    t_file *list = NULL;

    if ((flags_count = mx_parse_flags(argc, argv, &flags)) == -1)
        return (1);
    /*...*/

    last_sort_flag = get_last_sort_flag(argc - flags_count, argv);

    // parse args and add them to list
    /*...*/
    argv += flags_count;
    argc -= flags_count;
    for (int i = 0; i < argc; i++)
        mx_get_file_list(argv[i], flags, &list);
    mx_sort_by(&list, flags, last_sort_flag);
    /*...*/

    // display all
    mx_output(list, flags);

    // system("leaks -q uls");
    return 0;
}
