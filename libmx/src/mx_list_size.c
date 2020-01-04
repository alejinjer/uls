#include "libmx.h"

int mx_list_size(t_list *list) {
    int counter = 1;

    if (!list)
        return 0;
    while (list->next) {
        list = list->next;
        counter++;
    }
    return counter;
}
