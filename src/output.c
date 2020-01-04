#include "uls.h"

// тестовый вывод, нужно написать нормальный
void mx_output(t_file *list, int flags) { 
    char chmod[12];

    while (list) {
        if (flags & LS_L)
            mx_print_chmod(chmod, list);
        mx_printstr(list->name);
        mx_printstr("\n");
        if (S_ISDIR(list->st_mode) && list->subdirectories && (flags & LS_RR) 
            && strcmp(list->name, "..") != 0 
            && strcmp(list->name, ".") != 0)
            mx_output(list->subdirectories, flags);
        list = list->next;
    }
}

static char get_file_type(t_file *file) {
    if (S_ISREG(file->st_mode))
        return ('-');
    else if (S_ISDIR(file->st_mode))
        return ('d');
    else if (S_ISLNK(file->st_mode))
        return ('l');
    else if (S_ISBLK(file->st_mode))
        return ('b');
    else if (S_ISCHR(file->st_mode))
        return ('c');
    else if (S_ISSOCK(file->st_mode))
        return ('s');
    else if (S_ISFIFO(file->st_mode))
        return ('p');
    else
        return ('-');
}

static char get_file_acl(t_file *file) {
    acl_t tmp;
    char buf[101];

    if (listxattr(file->full_path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
        return ('@');
    if ((tmp = acl_get_file(file->full_path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

void mx_print_chmod(char chmod[12], t_file *file) {
    chmod[0] = get_file_type(file);
    chmod[1] = (S_IRUSR & file->st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & file->st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & file->st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & file->st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & file->st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & file->st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & file->st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & file->st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & file->st_mode) ? 'x' : '-';
    chmod[10] = get_file_acl(file);
    chmod[11] = '\0';
    if (S_ISUID & file->st_mode)
        chmod[3] = chmod[3] == '-' ? 'S' : 's';
    if (S_ISGID & file->st_mode)
        chmod[6] = chmod[6] == '-' ? 'S' : 's';
    if (S_ISVTX & file->st_mode)
        chmod[9] = chmod[9] == '-' ? 'T' : 't';
    mx_printstr(chmod);
}
