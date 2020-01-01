double mx_pow(double n, unsigned int pow) {
    double result = 1;

    if (pow == 0)
        return 1;
    if (pow == 1)
        return n;
    while (pow--)
        result *= n;
    return result;
}
