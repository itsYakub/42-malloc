#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static int _blk_dealloc(struct s_mallocBlock *);

static void *_blk_getalloc(struct s_mallocBlock *);

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
        ft_memset(chk->c_dat, 0, chk->c_siz);
        chk->c_use = 0;

        /* clear the memory block if no chunks is present... */
        if (!_blk_getalloc(blk)) {
            _blk_dealloc(blk);

            /* set the g_info's block to null... */
            g_info.blk.b_tny = 0;
        }
    }

    /* perform small deallocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
        /* clear the memory... */
        ft_memset(chk->c_dat, 0, chk->c_siz);
        chk->c_use = 0;

        /* clear the memory block if no chunks is present... */
        if (!_blk_getalloc(blk)) {
            _blk_dealloc(blk);

            /* set the g_info's block to null... */
            g_info.blk.b_sml = 0;
        }
    }

    /* perform large deallocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {
        if (chk == g_info.blk.b_lrg) {
            g_info.blk.b_lrg = g_info.blk.b_lrg->c_nxt;

            munmap(chk, sizeof(struct s_mallocChunk) + chk->c_siz);
        }

        else {
            struct s_mallocChunk *pchk = g_info.blk.b_lrg;
            for ( ; pchk->c_nxt != chk; pchk = pchk->c_nxt) { }

            pchk->c_nxt = (chk->c_nxt ? chk->c_nxt : 0);

            munmap(chk, sizeof(struct s_mallocChunk) + chk->c_siz);
        }
    }
}


static int _blk_dealloc(struct s_mallocBlock *blk) {
    if (!blk) { return (0); }

    /* set previous block of the next block to the current previous one... */
    if (blk->b_nxt) { blk->b_nxt->b_prv = blk->b_prv; }
    /* set next block of the previous block to the current next one... */
    if (blk->b_prv) { blk->b_prv->b_nxt = blk->b_nxt; }

    /* unmap current block... */
    size_t size = blk->b_cap + sizeof(struct s_mallocBlock);
    if (munmap(blk, size) == -1) {
        return (0);
    }
    return (1);
}


static void *_blk_getalloc(struct s_mallocBlock *blk) {
    struct s_mallocChunk *chk = blk->b_dat;
    /* iterate until the last chunk... */
    while (chk) {
        /* if chunk is actually used... */
        if (chk->c_use) {
            /* return it... */
            return (chk);
        }

        /* go to the next chunk in the block... */
        chk = chk->c_nxt;
    }

    /* no used chunks were found... */
    return (0);
}
