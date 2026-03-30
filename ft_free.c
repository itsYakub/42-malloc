#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

/* free:
 *  The free() function frees the memory space pointed to by ptr,
 *  which must have been returned by a previous call to malloc(), calloc(), or realloc().
 *  Otherwise, or if free(ptr) has already been called before, undefined behavior occurs.
 *  If ptr is NULL, no operation is per‐formed.
 * */
void free(void *ptr) {
    if (!ptr) { return; }

    struct s_mallocHeader *header = (struct s_mallocHeader *) (ptr) - 1;
    /* perform tiny deallocation... */
    if (header->h_siz > 0 && header->h_siz <= FT_MALLOC_TINY_SIZE) {
    
    }

    /* perform small deallocation... */
    else if (header->h_siz > FT_MALLOC_TINY_SIZE && header->h_siz <= FT_MALLOC_SMALL_SIZE) {

    }

    /* perform large deallocation... */
    else if (header->h_siz > FT_MALLOC_SMALL_SIZE) {
        int result = munmap(header, header->h_siz);
        if (result == -1) {
            return;
        }
    }
}
