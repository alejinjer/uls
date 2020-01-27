#include "uls.h"

static void size_less_thousand(off_t st_size, char *size);
static void size_more_thous(off_t num, double g, int pow, char *size);
static void size_less_thousand(off_t st_size, char *size);
static int round_num(double g);
static void add_pref(char *size, int pow);

char *mx_hr_size(off_t st_size) {
    char *size = mx_strnew(4);
    double g;
    int pow = 0;

    if (st_size < 1000)
        size_less_thousand(st_size, size);
    else if (st_size >= 1000)
    {
        pow = mx_hr_get_pow(st_size);
        g = st_size / mx_pow(2, pow);
        size_more_thous(st_size, g, pow, size);
    }
    return size;
}

static void size_more_thous(off_t num, double g, int pow, char *size) {
    if (g >= 9.95) {
        num = round_num(g);
        if (num < 999)
            mx_hr_write_number(size, num);
        else {
            num = round_num(g * 10);
            pow += 10;
            size[0] = num / 10 + 48;
            size[1] = '.';
            size[2] = num % 10 + 48;
        }
    }
    else {
        num = round_num(g * 10);
        size[0] = num / 10 + 48;
        size[1] = '.';
        size[2] = num % 10 + 48;
    }
    add_pref(size, pow);
}

static void size_less_thousand(off_t st_size, char *size) {
    off_t num = st_size;
    if (num == 0) {
      size = mx_strcpy(size, "  0B");
    }
    else if (st_size < 1000) {
      mx_hr_write_number(size, num);
        size[3] = 'B';
    }
}

static int round_num(double g) {
    off_t res;
    if (((off_t)(g * 10) % 10) >= 5)
        res = (off_t)(g * 10) /10 + 1;
    else
        res = (off_t)(g * 10) /10;
    return res;
}

static void add_pref(char *size, int pow) {
    switch (pow) {
        case 10:
            size[3] = 'K';
            break;
        case 20:
            size[3] = 'M';
            break;
        case 30:
            size[3] = 'G';
            break;
        case 40:
            size[3] = 'T';
            break;
        case 50:
            size[3] = 'P';
            break;
    }
}
