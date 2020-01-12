#include "uls.h"

int main(int argc, char *argv[]) {
    // parse flags
    /*...*/
    int flags_count;
    int flags;
    t_file *list = NULL;

    if ((flags_count = mx_parse_flags(argc, argv, &flags)) == -1)
        return (1);
    /*...*/

    // parse args and add them to list
    /*...*/
    argv += flags_count;
    argc -= flags_count;
    if (argc == 0)
        mx_get_data_set(".", flags, &list);
    else
        for (int i = 0; i < argc; i++)
            mx_get_data_set(argv[i], flags, &list);
    /*...*/
    // display all
    mx_output(list, flags);

    // system("leaks -q uls");
    return 0;
}
