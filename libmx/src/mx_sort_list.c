#include "libmx.h"

static void swap_nodes(t_list *n1, t_list *n2) {
    void *tmp = NULL;

    tmp = n1->data;
    n1->data = n2->data;
    n2->data = tmp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *tmp1 = lst;
    t_list *tmp2;

    if (!lst)
        return NULL;
    while (tmp1) {
        tmp2 = tmp1->next;
        while (tmp2) {
            if (cmp(tmp1->data, tmp2->data))
                swap_nodes(tmp1, tmp2);
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
    return lst;
}
