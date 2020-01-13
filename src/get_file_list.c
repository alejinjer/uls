#include "uls.h"

static char *make_full_path(char *dirname, char *file_name);

void mx_get_file_list(char *dirname, int flags, t_file **list) {
    DIR *d = opendir(dirname);
    t_dirent *entry = NULL;
    t_file *file = NULL;
    char *full_path = NULL;

    if (!d)
        return;
    while ((entry = readdir(d))) {
        full_path = make_full_path(dirname, entry->d_name);
        file = mx_create_file(entry->d_name, full_path);
        mx_lst_add_file(list, file);
        if (MX_ISDIR(file->st_mode) && (flags & LS_RR)) {
            if (mx_strcmp(file->name, "..") != 0 &&
                mx_strcmp(file->name, ".") != 0) {
                mx_get_file_list(file->full_path, flags, &file->subdirs);
            }
        } else if (MX_ISLNK(file->st_mode))
            readlink(file->full_path, file->symlink, NAME_MAX);
        mx_strdel(&full_path);
    }
    closedir(d);
    // mx_lst_sort(list, mx_sort_by_name, flags);   // это удалить (тестил аутпут)
    // mx_lst_sort(list, mx_sort_by_mtime, flags);  // это удалить (тестил аутпут)
    // ТУТ вызов функции, которая будет сортировать список в зависимости от флагов
}

static char *make_full_path(char *dirname, char *file_name) {
    char *full_path = mx_strnew(mx_strlen(dirname) + mx_strlen(file_name) + 1);

    full_path = mx_strcat(full_path, dirname);
    full_path = mx_strcat(full_path, "/");
    full_path = mx_strcat(full_path, file_name);
    return full_path;
}
