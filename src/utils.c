#include "uls.h"

void mx_ls_error(char *s, int error)
{
    if (error == USAGE)
    {
        mx_printerr("uls: illegal option -- ");
        write(2, s, 1);
        mx_terminate("\nusage: uls [ACRSUacflrtu1] [file ...]");
    }
    else if (error == ERRNO || error == MALL_ERR)
        mx_printerr("uls: ");
    if (error == ERRNO)
    {
        mx_printerr(s);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
    }
    if (error == USAGE || error == MALL_ERR)
        exit(1);
}

void mx_printnchar(char c, int n) {
    while (n) {
        mx_printchar(c);
        n--;
    }
}

int mx_intlength(int n) {
    int result = 1;

    while (n / 10) {
        ++result;
        n /= 10;
    }
    return result;
}

int mx_longlong_length(long long int n) {
    int result = 1;

    while (n / 10) {
        ++result;
        n /= 10;
    }
    return result;
}

int mx_list_max(t_file *files) {
    int max = 0;

    while (files) {
        if (mx_strlen(files->name) > max)
            max = mx_strlen(files->name);
        files = files->next;
    }
    return max;
}
