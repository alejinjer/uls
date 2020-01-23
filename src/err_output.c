#include "uls.h"

void mx_err_output(t_list *errors) {
    while (errors) {
        mx_printerr((char *)errors->data);
        errors = errors->next;
    }
}
