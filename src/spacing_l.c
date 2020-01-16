#include "uls.h"

int *mx_get_row_size(t_file *file) {
    struct group *gr = getgrgid(file->st_gid);
    static int size[7];
    int length = 0;

	size[5] = 3;
	size[6] = 3;
    while (file) {
        gr = getgrgid(file->st_gid);
        size[0] = MX_MAX(mx_intlength(file->st_blocks), size[0]);
        size[1] = MX_MAX(mx_intlength(file->st_nlink), size[1]);
        size[2] = MX_MAX(mx_strlen(getpwuid(file->st_uid)->pw_name), size[2]);
        if (gr)
            size[3] = MX_MAX(mx_strlen(gr->gr_name), size[3]);
        else 
            size[3] = MX_MAX(mx_intlength(file->st_gid), size[3]);
        if (!S_ISCHR(file->st_mode))
            length = mx_intlength(file->st_size);
        else {
            size[5] = MX_MAX(mx_intlength(MX_MAJOR(file->st_rdev)), size[5]);
            size[6] = MX_MAX(mx_intlength(MX_MINOR(file->st_rdev)), size[6]);
        }
        size[4] = MX_MAX(length, size[4]);
        file = file->next;
    }
    size[5] = MX_MAX(size[4] - size[6] - 1, size[5]);
    return size;
}
