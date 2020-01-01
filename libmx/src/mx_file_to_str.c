#include "libmx.h"

char *mx_file_to_str(const char *file)
{
    char *result = NULL;
    char *tmp = NULL;
    int file_descriptor;
    char buffer[1024];
    int read_result = 0;

    if (!file)
        return NULL;
    if ((file_descriptor = open(file, O_RDONLY)) < 0)
        return NULL;
    while ((read_result = read(file_descriptor, buffer, 1023)) > 0)
    {
        buffer[read_result] = '\0';
        tmp = mx_strjoin(result, buffer);
        mx_strdel(&result);
        result = mx_strdup(tmp);
        mx_strdel(&tmp);
    }
    if (close(file_descriptor) < 0)
        return NULL;
    return result;
}
