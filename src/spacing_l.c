#include "uls.h"

int *mx_get_row_size(t_file *file) {
    struct group *gr = getgrgid(file->st_gid);
    int *size = mx_memalloc(4 * sizeof(int));
    bool majorminor = false;

    while (file) {
        (MX_ISCHR(file->st_mode) || MX_ISBLK(file->st_mode)) 
            ? majorminor = true : 0;
        gr = getgrgid(file->st_gid);
        size[0] = MX_MAX(mx_intlength(file->st_nlink), size[0]);
        size[1] = MX_MAX(mx_strlen(getpwuid(file->st_uid)->pw_name), size[1]);
        size[2] = gr ? MX_MAX(mx_strlen(gr->gr_name), size[2])
                     : MX_MAX(mx_intlength(file->st_gid), size[2]);
        size[3] = MX_MAX(mx_longlong_length(file->st_size), size[3]);
        file = file->next;
    }
    if (majorminor)
        size[3] = size[3] < 8 ? 8 : size[3];
    return size;
}
