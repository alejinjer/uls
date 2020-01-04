int mx_sqrt(int x) {
    int result;
    int start = 1;
    int middle;
    int end = x / 2;

    if (x <= 0 || x == 1)
        return 0;
    if (x / 2 > 46340)
        end = 46340;
    while (start <= end) {
        middle = (start + end) / 2;
        if (middle * middle == x)
            return middle;
        if (middle * middle < x) {
            start = middle + 1;
            result = 0;
        } else
            end = middle - 1;
    }

    return result;
}
