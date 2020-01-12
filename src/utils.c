#include "uls.h"

void mx_ls_error(char *s, int error)
{
    if (error == USAGE)
    {
        mx_printerr("uls: illegal option -- ");
        write(2, s, 1);
        mx_terminate("\nusage: uls [-ARSUalrtu1] [file ...]");
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
    else if (error == ERRNO) 
        mx_printerr(strerror(errno));
    exit(1);
}

void mx_printnchar(char c, int n) {
    for (int i = 0; i < n; i++)
        mx_printchar(c);
}

int mx_intlength(int n) {
    int length = 0;

    while (n) {
        length++;
        n /= 10;
    }
    return length;
}

int mx_list_max(t_file *list) {
    int max = 0;

    while (list) {
        max = MAX(mx_strlen(list->name), max);
        list = list->next;
    }
    return max;
}
