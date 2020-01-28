#include "uls.h"

void mx_hr_write_number(char *size, off_t st_size) {
    int c;
    off_t num = st_size;

    for (c = 3; c > 0; c--) {
        if (num > 0) {
            size [c - 1] = num % 10 + 48;
            num /= 10;
        }
        else
            size[c - 1] = ' ';
    }
}

int mx_hr_get_pow(off_t st_size) {
    off_t num = st_size;
    int pow = 0;
    
    while (num >= 1000) {
        num /= 1024;
        pow += 10;
    }
    return pow;
}
