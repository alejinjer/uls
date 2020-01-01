#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    size_t needle_len = mx_strlen(needle);
    size_t haystack_len = mx_strlen(haystack);

    if (needle[0] == '\0')
        return (char *)haystack;
    if (haystack_len < needle_len)
        return NULL;
    while (*haystack) {
        if (mx_strncmp(haystack, needle, needle_len) == 0)
            return (char *)haystack;
        haystack += 1;
    }
    return NULL;
}
