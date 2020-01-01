#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    int index = -2;

    if (str) {
        index++;
        for (int i = 0; i < mx_strlen(str); i++) {
            if (str[i] == c) {
                index = i;
                return index;
            }
        }
    }
    return index;
}
