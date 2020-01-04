#include "libmx.h"

void mx_pop_front(t_list **head) {
    t_list *temp;

    if (!(*head) || !head)
        return;
    temp = *head;
    if (temp->next == NULL) {
        temp->data = NULL;
        free(temp);
    } else {
        *head = temp->next;
        temp->data = NULL;
        free(temp);
    }
}
