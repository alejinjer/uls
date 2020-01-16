#include "uls.h"

static unsigned int number_length(long long int number) {
    unsigned int length = 0;

    while (number) {
        number /= 10;
        length++;
    }
    return length;
}

char *mx_lltoa(long long int number) {
    unsigned int length = number_length(number);
    long long int tmp = number;
    char *result = NULL;

    result = mx_strnew(length);
    if (number == 0)
        return mx_strcpy(result, "0");
    if (number == -9223372036854775807)
        return mx_strcpy(result, "-9223372036854775807");
    tmp = number;
    for (unsigned int i = 0; i < length; i++) {
        if (tmp < 0) {
            result[length] = '-';
            tmp = -tmp;
        }
        result[i] = (tmp % 10) + '0';
        tmp /= 10;
    }
    mx_str_reverse(result);
    return result;
}
