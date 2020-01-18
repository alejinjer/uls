#include "uls.h"

void mx_print_uid(t_file *file, int nspaces) {
    t_passwd *passwd = getpwuid(file->st_uid);
    int len;
    
    passwd ? mx_printstr(passwd->pw_name) : mx_printint(file->st_uid);
    len = passwd ? mx_strlen(passwd->pw_name) : mx_intlength(file->st_uid);
    mx_printnchar(' ', nspaces - len + 2);
}
