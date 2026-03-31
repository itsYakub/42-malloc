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

    /* move the pointer to the metadata... */
    ptr = (char *) ptr - sizeof(struct s_mallocChunk);

    /* get the metadata structs... */
    struct s_mallocChunk *chk = (struct s_mallocChunk *) ptr;
    struct s_mallocBlock *blk = chk->c_blk;
    (void) blk;
    
    size_t size = chk->c_siz;
    /* perform tiny deallocation... */
    if (size > 0 && size <= FT_MALLOC_TINY_SIZE) {
        /* clear the memory... */
        chk->c_dat = ft_memset(chk->c_dat, 0, size);
        chk->c_use = 0;
    }

    /* perform small deallocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
    
    }

    /* perform large deallocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {

    }
}
