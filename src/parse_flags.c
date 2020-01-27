#include "uls.h"

static int parse_options(char *s, int *flags);

int mx_parse_flags(int argc, char **argv, int *flags) {
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

static int parse_options(char *s, int *flags) {
    int n;

    while (*(++s))
    {
        if ((n = mx_get_char_index("ACRSUacflrtu1hmp", *s)) == -1)
            mx_ls_error(s, USAGE);
        *flags |= (1 << n);
        if ((*s == 'l') || (*s == '1') || (*s == 'C')) {
            *flags &= (*s == 'l') ? ~(LS_ONE + LS_CC) : ~LS_L;
            *flags &= (*s == '1') ? ~(LS_L + LS_CC) : ~LS_ONE;
            *flags &= (*s == 'C') ? ~(LS_ONE + LS_L) : ~LS_CC;
        }
        if ((*s == 'U') || (*s == 'c') || (*s == 'u')) {
            *flags &= (*s == 'U') ? ~(LS_U + LS_C) : ~LS_UU;
            *flags &= (*s == 'c') ? ~(LS_UU + LS_U) : ~LS_C;
            *flags &= (*s == 'u') ? ~(LS_UU + LS_C) : ~LS_U;
        }
    }
    (*flags & LS_F) ? *flags &= ~(LS_T + LS_SS) : 0;
    (*flags & LS_SS) ? *flags &= ~LS_T : 0;
    return (1);
}
