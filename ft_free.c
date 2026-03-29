#include "./ft_malloc.h"

/* free:
 *  The free() function frees the memory space pointed to by ptr,
 *  which must have been returned by a previous call to malloc(), calloc(), or realloc().
 *  Otherwise, or if free(ptr) has already been called before, undefined behavior occurs.
 *  If ptr is NULL, no operation is per‐formed.
 * */
void free(void *ptr) {
    if (!ptr) { return; }

    /* ... */
}
