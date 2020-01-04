#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start = 0;
    int end = size - 1;
    int mid;

    *count = 0;
    while (start <= end) {
        *count += 1;
        mid = (start + end) / 2;
        if (mx_strcmp(arr[mid], s) < 0)
            start = mid + 1;
        else if (mx_strcmp(arr[mid], s) > 0)
            end = mid - 1;
        else
            return mid;
    }
    *count = 0;
    return -1;
}
