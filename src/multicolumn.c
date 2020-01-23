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

static int terminal_size() {
    struct winsize w;

    ioctl(0, TIOCGWINSZ, &w);
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

static t_list_info *multicolumn(t_file *files) {
    t_list_info *info = mx_memalloc(sizeof(t_list_info));
    int max = mx_list_max(files);
    int win_size = terminal_size();
    int words = total_words(files);
    
    info->lines = win_size / ((8 - (max % 8)) + max);
    if (words % info->lines)
        info->rows = (words / info->lines) + 1;
    else
        info->rows = words / info->lines;
    return info;
}

void mx_output_multicolumn(t_file *files) {
    t_list_info *info = multicolumn(files);
    int prev_strlen = 0;

    info->size = total_words(files);
    info->max_word_size = mx_list_max(files);
    for (int i = 0; i < info->rows; i++) {
        for (int j = 0; j < info->size; j+=info->rows) {
            if (j != 0) {
                mx_printnchar(' ', info->max_word_size - prev_strlen);
                mx_printchar('\t');
            }
            if (i + j < info->size) {
                mx_printstr(get_nth_element(files, i + j));
                prev_strlen = mx_strlen(get_nth_element(files, i + j));
            }
        }
        mx_printchar('\n');
    }
}
