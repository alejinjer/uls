int mx_strlen(const char *s) {
    int len = 0;
    int i = -1;

    while (s[++i]) {
        len++;
    }
    return len;
}
