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

#define LS_AA           1
#define LS_RR           2
#define LS_SS           4
#define LS_UU           8
#define LS_A            16
#define LS_L            32
#define LS_R            64
#define LS_T            128
#define LS_U            256
#define LS_ONE          512

#define MX_MAX(a, b)        b & ((a - b) >> 31) | a & (~(a - b) >> 31)

#define MX_ISBLK(m)      (((m) & S_IFMT) == S_IFBLK)     /* block special */
#define MX_ISCHR(m)      (((m) & S_IFMT) == S_IFCHR)     /* char special */
#define MX_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)     /* directory */
#define MX_ISFIFO(m)     (((m) & S_IFMT) == S_IFIFO)     /* fifo or socket */
#define MX_ISREG(m)      (((m) & S_IFMT) == S_IFREG)     /* regular file */
#define MX_ISLNK(m)      (((m) & S_IFMT) == S_IFLNK)     /* symbolic link */
#define MX_ISSOCK(m)     (((m) & S_IFMT) == S_IFSOCK)    /* socket */

/* Read, write, execute/search by user */
#define MX_IRUSR         0000400         /* [XSI] R for owner */
#define MX_IWUSR         0000200         /* [XSI] W for owner */
#define MX_IXUSR         0000100         /* [XSI] X for owner */
/* Read, write, execute/search by group */
#define MX_IRGRP         0000040         /* [XSI] R for group */
#define MX_IWGRP         0000020         /* [XSI] W for group */
#define MX_IXGRP         0000010         /* [XSI] X for group */
/* Read, write, execute/search by others */
#define MX_IROTH         0000004         /* [XSI] R for other */
#define MX_IWOTH         0000002         /* [XSI] W for other */
#define MX_IXOTH         0000001         /* [XSI] X for other */

#define MX_ISUID         0004000         /* [XSI] set user id on execution */
#define MX_ISGID         0002000         /* [XSI] set group id on execution */
#define MX_ISVTX         0001000         /* [XSI] directory restrcted delete */

#define MX_MAJOR(x)        ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define MX_MINOR(x)        ((int32_t)((x) & 0xffffff))

typedef struct stat t_stat;
typedef struct dirent t_dirent;
typedef struct passwd t_passwd;
typedef struct group t_group;
typedef struct s_file t_file;
typedef struct s_sort_stack_item t_sort_item;

struct s_file {
    char *name;
    char full_path[PATH_MAX];
    char symlink[NAME_MAX];
    mode_t st_mode;          /* File type and mode */
    nlink_t st_nlink;        /* Number of hard links */
    uid_t st_uid;            /* User ID of owner */
    gid_t st_gid;            /* Group ID of owner */
    dev_t st_rdev;           /* Device ID (if special file) */
    off_t st_size;           /* Total size, in bytes */
    blkcnt_t st_blocks;      /* Number of 512B blocks allocated */
    time_t st_mtim; /* Time of last modification */
    t_file *next;
    t_file *subdirs;
};

struct s_sort_stack_item {
    int level;
    t_file *item;
};

// parse_flags.c
int mx_parse_flags(int argc, char **argv, int *flags);

// utils.c
void mx_ls_error(char *s, int error);
void mx_printnchar(char c, int n);
int mx_intlength(int n);
int mx_longlong_length(long long int n);

// files.c
t_file *mx_create_file(char *path, char full_path[PATH_MAX]);
void mx_lst_add_file(t_file **list, t_file *file);

// get_file_list.c
void mx_explore_path(char *dirname, int flags, t_file **list);
void mx_handle_nonexistent(char *dirname, t_list **errors, 
                                t_file **files);

// sorting_algo.c
void mx_lst_sort(t_file **list,
                 bool (*cmp)(t_file *, t_file *, int reverse), int flags);

// sorting_flags.c
bool mx_sort_by_name(t_file *f1, t_file *f2, int reverse);
bool mx_sort_by_size(t_file *f1, t_file *f2, int reverse);
bool mx_sort_by_mtime(t_file *f1, t_file *f2, int reverse);
bool mx_sort_errors(void *a, void *b);

// print_total_nblocks.c
void mx_print_total_nblocks(t_file *list);

// print_chmod.c
void mx_output(t_file *list, int flags);
void mx_print_chmod(t_file *file, int nspaces);

// print_nlinks.c
void mx_print_nlinks(t_file *file, int nspaces);

// print_uid.c
void mx_print_uid(t_file *file, int nspaces);

// print_gid.c
void mx_print_gid(t_file *file, int nspaces);

// print_size.c
void mx_print_size(t_file *file, int nspaces);

// print_time.c
void mx_print_time(t_file *file);

// print_link.c
void mx_print_link(t_file *file);

//lltoa.c
char *mx_lltoa(long long int number);

//spacing_l.c
int *mx_get_row_size(t_file *file);

//print_major.c
void mx_print_major(t_file *file, int nspaces);

//print_minor.c
void mx_print_minor(t_file *file, int nspaces);

#endif
