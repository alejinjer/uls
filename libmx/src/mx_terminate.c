#include "libmx.h"

void mx_terminate(char *error_message) {
    mx_printerr(error_message);
    mx_printerr("\n");
    exit(1);
}
