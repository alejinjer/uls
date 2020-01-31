#include "uls.h"

static int total_words(t_file *files) {
    int total = 0;

    while (files) {
        if (files->name)
            total++;
        files = files->next;
    }
    return total;
}

int mx_terminal_size(int flags) {
    struct winsize w;

    if (isatty(1))
        ioctl(0, TIOCGWINSZ, &w);
    else if ((flags & LS_CC) || (flags & LS_M))
        w.ws_col = 80;
    else
        w.ws_col = 15;
    return w.ws_col;
}

static char *get_nth_element(t_file *head, int idx) {
    t_file *current = head;
    int counter = 0;

    while (current) {
        if (counter == idx)
            return (current->name);
        counter++;
        current = current->next;
    }
    return NULL;
}

static t_list_info *multicolumn(t_file *files, int flags) {
    t_list_info *info = mx_memalloc(sizeof(t_list_info));
    int max = mx_list_max(files);
    int win_size = mx_terminal_size(flags);
    int words = total_words(files);
    
    (info->lines = win_size / ((8 - (max % 8)) + max)) ? 0 : (info->lines = 1);
    if (words % info->lines)
        info->rows = (words / info->lines) + 1;
    else
        info->rows = words / info->lines;
    return info;
}

void mx_count_tabs(int max_len, int prev_len) {
    int spaces_count = 0;
    int tabs_count = 0;

    if (!(max_len % 8))
        spaces_count = max_len + 8;
    else {
        spaces_count = max_len;
        while (spaces_count % 8)
            spaces_count++;
    }
    tabs_count = (spaces_count - prev_len) / 8;
    if (!(prev_len % 8))
        tabs_count--;
    while (tabs_count--)
        mx_printchar('\t');
    mx_printchar('\t');
}

void mx_output_multicolumn(t_file *files, int flags) {
    t_list_info *info = multicolumn(files, flags);
    int prev_strlen = 0;

    info->size = total_words(files);
    info->max_word_size = mx_list_max(files);
    for (int i = 0; i < info->rows; i++) {
        for (int j = 0; j < info->size; j+=info->rows) {
            if (j != 0 && ((i + j) != mx_lst_size(files)))
                mx_count_tabs(info->max_word_size, prev_strlen);
            if (i + j < info->size) {
                mx_printstr(get_nth_element(files, i + j));
                prev_strlen = mx_strlen(get_nth_element(files, i + j));
            }
        }
        mx_printchar('\n');
    }
    free(info);
}
