#include "uls.h"

void mx_err_output(t_list *errors) {
    while (errors) {
        mx_printerr((char *)errors->data);
        errors = errors->next;
    }
}

bool mx_sort_errors(void *a, void *b) {
    return (mx_strcmp(a, b) > 0 ? 1 : 0);
}
