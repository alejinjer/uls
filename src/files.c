#include "uls.h"

t_file *mx_create_file(char *path, char *full_path)
{
    t_file *file = (t_file *)mx_memalloc(sizeof(t_file));
	t_stat stat;

	lstat(full_path, &stat);
	mx_memcpy((void*)file->full_path, (void*)full_path, PATH_MAX);
	file->name = mx_strdup(path);
	file->st_mode = stat.st_mode;
	file->st_nlink = stat.st_nlink;
	file->st_uid = stat.st_uid;
	file->st_gid = stat.st_gid;
	file->st_size = stat.st_size;
	file->st_rdev = stat.st_rdev;
	file->st_blocks = stat.st_blocks;
	file->st_mtim = stat.st_mtime;
    return file;
}

void mx_lst_add_file(t_file **list, t_file *file) {
    if (!list || !*list) {
		*list = file;
		return;
	}
	file->next = *list;
    *list = file;
}
