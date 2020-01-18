#include "uls.h"

static char get_file_type(t_file *file) {
    if (MX_ISREG(file->st_mode))
        return ('-');
    else if (MX_ISDIR(file->st_mode))
        return ('d');
    else if (MX_ISLNK(file->st_mode))
        return ('l');
    else if (MX_ISBLK(file->st_mode))
        return ('b');
    else if (MX_ISCHR(file->st_mode))
        return ('c');
    else if (MX_ISSOCK(file->st_mode))
        return ('s');
    else if (MX_ISFIFO(file->st_mode))
        return ('p');
    else
        return ('-');
}

static char get_file_acl(t_file *file) {
    acl_t tmp;

    if (listxattr(file->full_path, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');
    if ((tmp = acl_get_file(file->full_path, ACL_TYPE_EXTENDED))) {
        acl_free(tmp);
        return ('+');
    }
    return (' ');
}

void mx_print_chmod(t_file *file, int nspaces) {
    char chmod[12];

    chmod[0] = get_file_type(file);
    chmod[1] = (MX_IRUSR & file->st_mode) ? 'r' : '-';
    chmod[2] = (MX_IWUSR & file->st_mode) ? 'w' : '-';
    chmod[3] = (MX_IXUSR & file->st_mode) ? 'x' : '-';
    chmod[4] = (MX_IRGRP & file->st_mode) ? 'r' : '-';
    chmod[5] = (MX_IWGRP & file->st_mode) ? 'w' : '-';
    chmod[6] = (MX_IXGRP & file->st_mode) ? 'x' : '-';
    chmod[7] = (MX_IROTH & file->st_mode) ? 'r' : '-';
    chmod[8] = (MX_IWOTH & file->st_mode) ? 'w' : '-';
    chmod[9] = (MX_IXOTH & file->st_mode) ? 'x' : '-';
    chmod[10] = get_file_acl(file);
    chmod[11] = '\0';
    MX_ISUID & file->st_mode ? (chmod[3] = chmod[3] == '-' ? 'S' : 's') : 0;
    MX_ISGID & file->st_mode ? (chmod[6] = chmod[6] == '-' ? 'S' : 's') : 0;
    MX_ISVTX & file->st_mode ? (chmod[9] = chmod[9] == '-' ? 'T' : 't') : 0;
    mx_printstr(chmod);
    mx_printnchar(' ', nspaces);
}
