#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    int size_arr;
    char **arr;
    int index = 0;
    int j = 0;

    if (!s || mx_get_char_index(s, c) == -1)
        return NULL;
    size_arr = mx_count_words(s, c);
    if (!(arr = malloc(sizeof(char *) * (size_arr + 1))))
        return NULL;
    arr[size_arr] = NULL;
    while (*s) {
        index = mx_get_char_index(s, c);
        index = index == -1 ? mx_strlen(s) : index;
        if (index) {
            arr[j] = mx_strndup(s, index);
            s += mx_strlen(arr[j++]) - 1;
        }
        s++;
    }
    return arr;
}
