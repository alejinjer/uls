int mx_strcmp(const char *s1, const char *s2) {
    for (int i = 0;; i++) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        if (!s1[i])
            return 0;
    }
    return 0;
}
