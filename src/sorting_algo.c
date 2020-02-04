#include "uls.h"

static t_file *intersect(t_file *f1, t_file *f2,
                         bool (*cmp)(t_file *, t_file *, int reverse),
                         int flags) {
    t_file *pCurItem;
    t_file *result;
    int r = (flags & LS_R);

    cmp(f1, f2, r) <= 0 ? ((pCurItem = f1) && (f1 = f1->next))
                        : ((pCurItem = f2) && (f2 = f2->next));
    result = pCurItem;
    while (f1 && f2)
        cmp(f1, f2, r) <= 0
            ? ((pCurItem->next = f1) && (pCurItem = f1)) && (f1 = f1->next)
            : ((pCurItem->next = f2) && (pCurItem = f2)) && (f2 = f2->next);
    pCurItem->next = (f1 ? f1 : f2);
    return result;
}

static void intersect_cycle(int *stack_pos, t_sort_item (*stack)[31],
                            bool (*cmp)(t_file *, t_file *, int reverse),
                            int flags) {
    while ((*stack_pos > 1)
        && (*stack)[*stack_pos - 1].level == (*stack)[*stack_pos - 2].level) {
        (*stack)[*stack_pos - 2].item = intersect(
            (*stack)[*stack_pos - 2].item,
            (*stack)[*stack_pos - 1].item, cmp, flags);
        ++((*stack)[*stack_pos - 2].level);
        --(*stack_pos);
    }
}

void mx_lst_sort(t_file **list,
                 bool (*cmp)(t_file *, t_file *, int reverse), int flags) {
    t_sort_item stack[31];
    int stack_pos = 0;
    t_file *ptr = *list;

    while (ptr && (stack[stack_pos].level = 1)
        && (stack[stack_pos].item = ptr)) {
        ptr = ptr->next;
        stack[stack_pos++].item->next = NULL;
        intersect_cycle(&stack_pos, &stack, cmp, flags);
    }
    while (stack_pos > 1) {
        stack[stack_pos - 2].item = intersect(
            stack[stack_pos - 2].item, stack[stack_pos - 1].item, cmp, flags);
        ++(stack[stack_pos - 2].level) && --stack_pos;
    }
    stack_pos > 0 ? *list = stack[0].item : 0;
}
