#include "uls.h"

void mx_get_data_set(char *dirname, int flags, t_file **list) {
    DIR *d = opendir(dirname);
    t_dirent *entry = NULL;
    t_file *file = NULL;
    char *full_path = NULL;

    if (!d)
        return;
    while ((entry = readdir(d))) {
        full_path = mx_strdup(dirname);
        full_path = mx_strcat(full_path, "/");
        full_path = mx_strcat(full_path, entry->d_name);
        file = mx_create_file(entry->d_name, full_path);
        mx_lst_add_file(list, file);
        if (S_ISDIR(file->st_mode) && (flags & LS_RR)) {
            if (mx_strcmp(file->name, "..") != 0 &&
                mx_strcmp(file->name, ".") != 0) {
                mx_get_data_set(file->full_path, flags, &file->subdirectories);
            }
        }
        mx_strdel(&full_path);
    }
    closedir(d);
    mx_lst_sort(list, mx_sort_by_name, flags);  // это удалить (тестил аутпут)
    // ТУТ вызов функции, которая будет сортировать список в зависимости от флагов
}
