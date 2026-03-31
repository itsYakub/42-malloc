#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static size_t _blk_getused(struct s_mallocBlock *);

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
    
    size_t size = chk->c_siz;
    /* perform tiny deallocation... */
    if (size > 0 && size <= FT_MALLOC_TINY_SIZE) {
        /* clear the memory... */
        chk->c_dat = ft_memset(chk->c_dat, 0, size);
        chk->c_use = 0;

        /* if all the chunks are cleared, release the block... */
        if (!_blk_getused(blk)) {
            /* configure neighbouring metadata blocks... */
            if (blk->b_prv) { blk->b_prv->b_nxt = blk->b_nxt; }
            if (blk->b_nxt) { blk->b_nxt->b_prv = blk->b_prv; }

            /* release the current block... */
            if (munmap(blk, blk->b_siz) == -1) {
                return;
            }

            /* and now, for safety, set the block pointer in global state to null... */
            g_info.blk.b_tny = 0;
        }
    }

    /* perform small deallocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
    
    }

    /* perform large deallocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {

    }
}

static size_t _blk_getused(struct s_mallocBlock *blk) {
    /* null-check... */
    if (!blk) { return (0); }

    /* iterate over the block to find free chunk... */
    struct s_mallocChunk *chk = blk->b_dat;
    
    size_t siz = 0;
    for (size_t i = 0; i < 100; i++) {
        /* if chunk is used, increase the siz... */
        if (chk->c_use) {
            siz++;
        }
        
        chk = chk->c_nxt;
    }

    /* return the siz... */
    return (siz);
}
