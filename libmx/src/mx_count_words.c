#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int counter = 0;
    int flag = 0;

    if (!str)
        return -1;
    while (*str) {
        if (*str == c)
            flag = 0;
        else if (!flag) {
            flag = 1;
            counter++;
        }
        str++;
    }
    return counter;
}
