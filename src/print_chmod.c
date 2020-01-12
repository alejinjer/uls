#include "uls.h"

void mx_print_nlinks(t_file *file) {
    mx_printint(file->st_nlink);
}

void mx_print_uid(t_file *file) {
    mx_printstr(getpwuid(file->st_uid)->pw_name);
}

void mx_print_gid(t_file *file) {
    struct group *gr = getgrgid(file->st_gid);

    gr ? mx_printstr(gr->gr_name) : mx_printint(file->st_gid);
}

void mx_print_size(t_file *file) {
    mx_printstr(mx_lltoa(file->st_size));
}

void mx_print_time(t_file *file) {
	char	*s = NULL;
    char	*s1 = mx_strnew(12);

    s = ctime(&(file->st_mtim.tv_sec)) + 4;
    s1 = mx_strncpy(s1, s, 12);

	mx_printstr(s1);
}
void mx_print_major(t_file *file) {
    mx_printint(major(file->st_rdev));
}

void mx_print_minor(t_file *file) {
    mx_printint(minor(file->st_rdev));
}

// тестовый вывод, нужно написать нормальный
void mx_output(t_file *list, int flags) { 
    char chmod[12];
    int blocks = 0;
    int *size = mx_get_row_size(list, &blocks);
    int max_size = mx_list_max(list);

    while (list) {
        if (flags & LS_L) {
            mx_print_chmod(chmod, list);
            mx_printnchar(' ', size[1] - mx_intlength(list->st_nlink) + 1);
            mx_print_nlinks(list);
            mx_printnchar(' ', size[2] - mx_strlen(getpwuid(list->st_uid)->pw_name) + 1);
            mx_print_uid(list);
            mx_printnchar(' ', 2);
            mx_print_gid(list);
            if (list->st_gid)
                mx_printnchar(' ', size[3] - mx_intlength(list->st_gid));
            else
                mx_printnchar(' ', size[3] - mx_strlen(getgrgid(list->st_gid)->gr_name));
            if (chmod[0] != 'c' && chmod[0] != 'b') {
                mx_printnchar(' ', size[7] - mx_intlength(list->st_size) + 2);
                mx_print_size(list);
            }
            else {
                mx_print_major(list);
                mx_printstr(", ");
                mx_printnchar(' ', size[6] - mx_intlength(minor(list->st_rdev) - 1));
                mx_print_minor(list);
            }
            mx_printchar(' ');
            mx_print_time(list);
            mx_printchar(' ');
            mx_printstr(list->name);
            mx_printchar('\n');
        }
        else if (flags & LS_ONE) {
            mx_printstr(list->name); 
            mx_printchar('\n');
        }
        else {
            mx_printstr(list->name);
            if (list->next) {
                mx_printnchar(' ', max_size - mx_strlen(list->name));
                mx_printchar('\t');
            } else {
                mx_printchar('\n');
            }
        }
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

    if (listxattr(file->full_path, NULL, 0, XATTR_NOFOLLOW) > 0)
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
