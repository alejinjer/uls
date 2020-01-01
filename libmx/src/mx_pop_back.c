#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list *temp;

    if (!(*head) || !head)
        return;
    temp = *head;
    if (temp->next == NULL) {
        temp->data = NULL;
        free(temp);
    } else {
        while (temp->next->next)
            temp = temp->next;
        temp->next->data = NULL;
        free(temp->next);
    }
}
