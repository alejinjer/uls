#include "uls.h"

void mx_print_uid(t_file *file) {
    t_passwd *passwd = getpwuid(file->st_uid);
    
    passwd ? mx_printstr(passwd->pw_name) : mx_printint(file->st_uid);
}
