#include "uls.h"

static void output(t_file *list) {
    while (list) {
        printf("%s\n", list->name);
        if (S_ISDIR(list->st_mode) && list->subdirectories && strcmp(list->name, "..") != 0 &&
            strcmp(list->name, ".") != 0)
            output(list->subdirectories);
        list = list->next;
    }
}

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
    for (int i = 0; i < argc; i++)
        mx_get_file_list(argv[i], flags, &list);
    /*...*/

    // display all
    output(list);

    return 0;
}
