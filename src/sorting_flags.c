#include "uls.h"

bool mx_sort_by_name(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (mx_strcmp(f1->name, f2->name) > 0 ? 1 : 0);
    return (mx_strcmp(f1->name, f2->name) > 0 ? 0 : 1);
}

// -S
bool mx_sort_by_size(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_size >= f2->st_size) ? 0 : 1;
    return (f1->st_size > f2->st_size) ? 1 : 0;
}

// -t
bool mx_sort_by_mtime(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_mtimespec.tv_sec >= f2->st_mtimespec.tv_sec) ? 0 : 1;
    return (f1->st_mtimespec.tv_sec > f2->st_mtimespec.tv_sec) ? 1 : 0;
}

// -u
bool mx_sort_by_atime(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_atimespec.tv_sec >= f2->st_atimespec.tv_sec) ? 0 : 1;
    return (f1->st_atimespec.tv_sec > f2->st_atimespec.tv_sec) ? 1 : 0;
}

// -U
bool mx_sort_by_btime(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_btimespec.tv_sec >= f2->st_btimespec.tv_sec) ? 0 : 1;
    return (f1->st_mtimespec.tv_sec > f2->st_mtimespec.tv_sec) ? 1 : 0;
}

// -c
bool mx_sort_by_ctime(t_file *f1, t_file *f2, int reverse) {
    if (!reverse)
        return (f1->st_ctimespec.tv_sec >= f2->st_ctimespec.tv_sec) ? 0 : 1;
    return (f1->st_ctimespec.tv_sec > f2->st_ctimespec.tv_sec) ? 1 : 0;
}

bool mx_sort_errors(void *a, void *b) {
    return (mx_strcmp(a, b) > 0 ? 1 : 0);
}
