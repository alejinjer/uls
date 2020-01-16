#include "uls.h"

static char *make_full_path(char *dirname, char *file_name);

void mx_handle_nonexistent(char *dirname, t_list **errors, 
                                t_file **files) {
    t_stat stat;
    t_file *file = NULL;
    DIR *d = opendir(dirname);

    if (!d) {
        if (lstat(dirname, &stat) == -1) {
            char *error_message = mx_strnew(mx_strlen(dirname) 
                                    + mx_strlen(strerror(errno)) + 7);
            mx_strcat(error_message, "uls: ");
            mx_strcat(error_message, dirname);
            mx_strcat(error_message, ": ");
            mx_strcat(error_message, strerror(errno));
            mx_strcat(error_message, "\n");
            mx_push_front(errors, error_message);
        }
        else {
            file = mx_create_file(dirname, mx_strdup(dirname));
            mx_lst_add_file(files, file);
            if (MX_ISLNK(file->st_mode))
                readlink(file->full_path, file->symlink, NAME_MAX);
        }
    }
    else
        closedir(d);
}

void mx_explore_path(char *dirname, int flags, t_file **list) {
    DIR *d = opendir(dirname);
    t_dirent *entry = NULL;

    if (!d) {
        // mx_ls_error(dirname, ERRNO);
        return;
    }
    while ((entry = readdir(d))) {
        char *full_path = make_full_path(dirname, entry->d_name);
        t_file *file = mx_create_file(entry->d_name, full_path);
        
        mx_lst_add_file(list, file);
        (MX_ISDIR(file->st_mode) && (flags & LS_RR)
            && (mx_strcmp(file->name, "..") != 0
            && mx_strcmp(file->name, ".") != 0))
            ? mx_explore_path(file->full_path, flags, &file->subdirs) : (void)0;
        if (MX_ISLNK(file->st_mode))
            readlink(file->full_path, file->symlink, NAME_MAX);
        mx_strdel(&full_path);
    }
    closedir(d);
}

static char *make_full_path(char *dirname, char *file_name) {
    char *full_path = mx_strnew(mx_strlen(dirname) + mx_strlen(file_name) + 1);

    full_path = mx_strcat(full_path, dirname);
    full_path = mx_strcat(full_path, "/");
    full_path = mx_strcat(full_path, file_name);
    return full_path;
}
