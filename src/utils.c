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
    if (error == USAGE || error == MALL_ERR)
        exit(1);
}
