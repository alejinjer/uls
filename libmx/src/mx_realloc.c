#include "libmx.h"

static size_t get_size_to_copy(void *p, void *r) {
    return malloc_size(p) < malloc_size(r) ? malloc_size(p) : malloc_size(r);
}

static void copy_data(void *ptr, void *new_ptr) {
    size_t size_to_copy = get_size_to_copy(ptr, new_ptr);
    new_ptr = mx_memcpy(new_ptr, ptr, size_to_copy);
    free(ptr);
}

void *mx_realloc(void *ptr, size_t size) {
    void *result = NULL;

    if (!ptr && size)
        return malloc(size);
    if (!size && ptr) {
        free(ptr);
        return malloc(0);
    }
    if (!(result = malloc(size)))
        return NULL;
    if (malloc_size(ptr) < malloc_size(result))
        copy_data(ptr, result);
    else {
        if (malloc_size(ptr) < size - 32)
            copy_data(ptr, result);
        else
            result = ptr;
    }
    return result;
}
