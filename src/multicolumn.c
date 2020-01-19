#include "uls.h"


static int total_words(t_file *files) {
    int total = 0;

    // while (dirs) {
    //     if (dirs->name)
    //         total++;
    //     dirs = dirs->next;
    // }
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

t_lines *mx_multicolumn(t_file *files) {
    t_lines *rows = mx_memalloc(sizeof(t_lines));
    int max = mx_list_max(files);
    int win_size = terminal_size();
    int words = total_words(files);
    
    rows->lines = win_size / (((max / 8) * 8) + 8);
    if ((words % rows->lines) != 0)
        rows->rows = (words / rows->lines) + 1;
    else
        rows->rows = words / rows->lines;
    return rows;
}

void mx_output_multicolumn(t_file *files) {
    t_lines *rows = mx_multicolumn(files);
    //int max = mx_list_max(files);

    while (files) {
        
        files = files->next;
    }

}
