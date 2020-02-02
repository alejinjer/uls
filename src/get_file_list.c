#include "uls.h"

static char *make_error_message(char *dirname) {
    char *error_message = mx_strnew(mx_strlen(dirname)
                                    + mx_strlen(strerror(errno)) + 8);

    mx_strcat(error_message, "uls: ");
    mx_strcat(error_message, dirname);
    mx_strcat(error_message, ": ");
    mx_strcat(error_message, strerror(errno));
    mx_strcat(error_message, "\n");
    return error_message;
}

static void open_error(t_file **list, char *dirname) {
    char *filename = mx_memrchr(dirname, '/', mx_strlen(dirname));
    char *error_message = make_error_message(filename + 1);
    t_file *err = mx_create_file("", "");

    err->error = error_message;
    mx_lst_add_file(list, err);
}

t_list *mx_process_args(char *argv[], t_file **files,
                        t_file **dirs, int flags)
{
    DIR *d = NULL;
    t_list *errors = NULL;
    t_file *dir_ptr = NULL;

    while (*argv) {
        (d = opendir(*argv))
            ? mx_lst_add_file(dirs, mx_create_file(*argv, *argv))
            : (void)0;
        !d ? mx_handle_nonexistent(*argv, &errors, files, dirs) : (void)0;
        d ? closedir(d) : 0;
        ++argv;
    }
    (!*dirs && !errors && !*files)
        ? mx_lst_add_file(dirs, mx_create_file(".", "."))
        : (void)0;
    dir_ptr = *dirs;
    while (dir_ptr) {
        mx_explore_path(dir_ptr->name, flags, &dir_ptr->subdirs);
        dir_ptr = dir_ptr->next;
    }
    return errors;
}

void mx_handle_nonexistent(char *dirname, t_list **errors,
                           t_file **files, t_file **dirs)
{
    t_stat stat;
    t_file *file = NULL;

    if (lstat(dirname, &stat) == -1)
        mx_push_front(errors, make_error_message(dirname));
    else if (stat.st_mode) {
        file = mx_create_file(dirname, dirname);
        mx_lst_add_file(files, file);
    }
    else {
        file = mx_create_file(dirname, dirname);
        file->error = make_error_message(dirname);
        mx_lst_add_file(dirs, file);
    }
}

void mx_explore_path(char *dirname, int flags, t_file **list) {
    DIR *d = opendir(dirname);
    t_dirent *entry = NULL;

    !d ? open_error(list, dirname) : (void)0;
    while (d && (entry = readdir(d))) {
        if (entry->d_name[0] == '.' && !(flags & LS_AA) && !(flags & LS_A))
            continue;
        else if ((!mx_strcmp(entry->d_name, ".")
            || !mx_strcmp(entry->d_name, "..")) && !(flags & LS_A))
        {
            continue;
        }
        t_file *file = mx_create_file(entry->d_name, dirname);

        mx_lst_add_file(list, file);
        (MX_ISDIR(file->st_mode) && (flags & LS_RR)
            && (mx_strcmp(file->name, "..") && mx_strcmp(file->name, ".")))
            ? mx_explore_path(file->full_path, flags, &file->subdirs)
            : (void)0;
    }
    d ? closedir(d) : 0;
}
