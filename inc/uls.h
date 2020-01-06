#ifndef ULS_HEADER
#define ULS_HEADER

#include "libmx.h"
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <time.h>


#define PATH_MAX 1024

typedef enum e_error {
    ERRNO,
    USAGE,
    MALL_ERR
} t_error;

/*
** -A (LS_AA) to display hidden files;
** -R (LS_RR) recursively list subfolders encountered;
** -S (LS_SS) sort by size;
** -U (LS_UU) sort by creation date;
** -a (LS_A) to display hidden files, current folder and previous folder;
** -l (LS_L) to get more details, -d to display current folder only;
** -r (LS_R) reverse the order of the sort to get reverse ASCII order or the
** oldest entries first (or largest files last, if combined with sort by size;
** -t (LS_T) sort by time modified;
** -u (LS_U) sort by last time of access;
** -1 (LS_ONE) to display results on one column;
*/

#define LS_AA 1
#define LS_RR 2
#define LS_SS 4
#define LS_UU 8
#define LS_A 16
#define LS_L 32
#define LS_R 64
#define LS_T 128
#define LS_U 256
#define LS_ONE 512

/*
	file mode, number of links, owner name, group name, 
	number of bytes in the file, abbreviated month, 
	day-of-month file was last modified, hour file last modified, 
	minute file last modified, and the pathname.
*/

typedef struct stat t_stat;
typedef struct dirent t_dirent;
typedef struct s_file t_file;
typedef struct s_sort_stack_item t_sort_item;

struct s_file {
    char *name;
    char full_path[PATH_MAX];
    mode_t st_mode;          /* File type and mode */
    nlink_t st_nlink;        /* Number of hard links */
    uid_t st_uid;            /* User ID of owner */
    gid_t st_gid;            /* Group ID of owner */
    dev_t st_rdev;           /* Device ID (if special file) */
    off_t st_size;           /* Total size, in bytes */
    blkcnt_t st_blocks;      /* Number of 512B blocks allocated */
    struct timespec st_atim; /* Time of last access */
    struct timespec st_mtim; /* Time of last modification */
    struct timespec st_ctim; /* Time of last status change */
    t_file *next;
    t_file *subdirectories;
};

struct s_sort_stack_item {
    int level;
    t_file *item;
};

// parse_flags.c
int mx_parse_flags(int argc, char **argv, int *flags);

// utils.c
void mx_ls_error(char *s, int error);

// files.c
// t_file *mx_create_file(char *path);
t_file *mx_create_file(char *path, char *full_path);
void mx_lst_add_file(t_file **list, t_file *file);

// get_file_list.c
void mx_get_data_set(char *dirname, int flags, t_file **list);

// sorting.c
void mx_lst_sort(t_file **list,
                 bool (*cmp)(t_file *, t_file *, int reverse), int flags);

// sorting_flags.c
bool mx_sort_by_name(t_file *f1, t_file *f2, int reverse);

// output.c
void mx_output(t_file *list, int flags);
void mx_print_chmod(char chmod[12], t_file *file);

//lltoa.c
char *mx_lltoa(long long int number);

#endif
