#include "uls.h"

static char *make_full_path(char *file_name, char *dirname);

t_file *mx_create_file(char *name, char *dirname)
{
    t_file *file = (t_file *)mx_memalloc(sizeof(t_file));
	t_stat stat;

	file->name = mx_strdup(name);
	file->full_path = make_full_path(name, dirname);
	lstat(file->full_path, &stat);
	file->st_mode = stat.st_mode;
	if (MX_ISLNK(file->st_mode))
            readlink(file->full_path, file->symlink, NAME_MAX);
	file->st_nlink = stat.st_nlink;
	file->st_uid = stat.st_uid;
	file->st_gid = stat.st_gid;
	file->st_size = stat.st_size;
	file->st_rdev = stat.st_rdev;
	file->st_blocks = stat.st_blocks;
	file->st_atimespec = stat.st_atimespec;
	file->st_mtimespec = stat.st_mtimespec;
	file->st_ctimespec = stat.st_ctimespec;
	file->st_btimespec = stat.st_birthtimespec;
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

int mx_lst_size(t_file *list) {
	int result = 0;

	while (list) {
  		++result;
  		list = list->next;
 	}
 	return result;
}

static char *make_full_path(char *file_name, char *dirname) {
    char *full_path = mx_strnew(mx_strlen(dirname) + mx_strlen(file_name) + 1);

	if (mx_strcmp(file_name, dirname) == 0)
		mx_strcat(full_path, dirname);
	else {
		full_path = mx_strcat(full_path, dirname);
		if (mx_strcmp(dirname, "/"))
			full_path = mx_strcat(full_path, "/");
		full_path = mx_strcat(full_path, file_name);
	}
    return full_path;
}
