#include "./ft_malloc.h"

/* malloc:
 *  The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.
 *  If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
 * */
void *malloc(size_t size) {
    if (!size) { return (0); }

    void *ptr = 0;

    /* ... */

    return (ptr);
}
