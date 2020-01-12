#include "uls.h"


int *mx_get_row_size(t_file *file, int *blocks) {
    int length;
    struct group *gr = getgrgid(file->st_gid);
    static int size[8];

    size[5] = 3;
    size[6] = 3;
    while (file) {
        size[0] = MAX(mx_intlength(file->st_blocks), size[0]);
        size[1] = MAX(mx_intlength(file->st_nlink), size[1]);
        size[2] = MAX(mx_strlen(getpwuid(file->st_uid)->pw_name), size[2]);
        if (gr)
            size[3] = MAX(mx_strlen(gr->gr_name), size[3]);
        else 
            size[3] = MAX(mx_intlength(file->st_gid), size[3]);
        if (!S_ISCHR(file->st_mode))
            length = mx_intlength(file->st_size);
        else {
            size[5] = MAX(mx_intlength(major(file->st_rdev)), size[5]);
            size[6] = MAX(mx_intlength(minor(file->st_rdev)), size[6]);
            length = size[5] + size[6] + 2;
        }
        size[7] = MAX(mx_intlength(file->st_size), size[7]);
        *blocks += file->st_blocks;
        file = file->next;
    }
    size[5] = MAX(size[4] - size[6] - 1, size[5]);

    return size;
}
