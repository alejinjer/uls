#include "uls.h"

void mx_print_time(t_file *file) {
    char *temp_time = ctime(&(file->st_mtimespec.tv_sec));
    char *result = mx_strnew(12);
    time_t now = time(NULL);

    if ((now - 15778463) > file->st_mtimespec.tv_sec
        || now < file->st_mtimespec.tv_sec)
    {
        result = mx_strncpy(result, temp_time + 4, 6);
        mx_strcpy(result + 6, "  ");
        mx_strncpy(result + 8, temp_time + 20, 4);
    }
    else
        result = mx_strncpy(result, temp_time + 4, 12);
    mx_printstr(result);
    mx_printchar(' ');
    mx_strdel(&result);
}
