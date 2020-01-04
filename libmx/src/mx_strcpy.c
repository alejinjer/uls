char *mx_strcpy(char *dst, const char *src) {
    int i = -1;

    while (src[++i])
        dst[i] = src[i];
    while (dst[i]) {
        dst[i] = '\0';
        i++;
    }
    return dst;
}
