#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *node;
    t_list *temp;

    if (!list)
        return;
    node = mx_create_node(data);
    temp = *list;
    if (!*list) {
        *list = node;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = node;
}
