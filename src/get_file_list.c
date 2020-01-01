#include "uls.h"

void mx_get_file_list(char *dirname, int flags, t_file **list) {
    DIR *d = opendir(dirname);
    t_dirent *entry = NULL;
    t_file *file = NULL;

    if (!d)
        return;
    while ((entry = readdir(d))) {
        file = mx_create_file(entry->d_name);
        mx_lst_add_file(list, file);
        if ((entry->d_type & DT_DIR) && (flags & LS_RR)) {
            if (mx_strcmp(entry->d_name, "..") != 0 &&
                mx_strcmp(entry->d_name, ".") != 0) {
                mx_strcat(file->full_path, dirname);
                mx_strcat(file->full_path, "/");
                mx_strcat(file->full_path, entry->d_name);
                mx_get_file_list(file->full_path, flags, &file->subdirectories);
            }
        }
    }
    closedir(d);
}
