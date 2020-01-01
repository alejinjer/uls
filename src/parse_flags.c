#include "uls.h"

static int parse_options(char *s, int *flags);

int mx_parse_flags(int argc, char **argv, int *flags)
{
    int i = 0;

    *flags = 0;
    while (++i < argc && argv[i][0] == '-' && argv[i][1])
    {
        if (argv[i][1] == '-' && argv[i][2])
			return (i + 1);
        if (!parse_options(argv[i], flags))
            return (-1);
    }
    return (i);
}

static int parse_options(char *s, int *flags)
{
    int n;

    while (*(++s))
    {
        if ((n = mx_get_char_index("ARSalrt1", *s)) == -1)
            mx_ls_error(s, USAGE);
        *flags |= (1 << n);
        if ((*s == 'l') || (*s == '1'))
            *flags &= (*s == 'l') ? ~LS_ONE : ~LS_L;
    }
    return (1);
}
