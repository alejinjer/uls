#include "uls.h"

bool mx_sort_by_name(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (mx_strcmp(f1->name, f2->name) > 0 ? 1 : 0);
    return (mx_strcmp(f1->name, f2->name) < 0 ? 1 : 0);
}
