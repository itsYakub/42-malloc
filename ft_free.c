#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static int _blk_dealloc(struct s_mallocBlock *);

static void *_blk_getalloc(struct s_mallocBlock *);

static int _chk_dealloc(struct s_mallocChunk *);

/* free:
 *  The free() function frees the memory space pointed to by ptr,
 *  which must have been returned by a previous call to malloc(), calloc(), or realloc().
 *  Otherwise, or if free(ptr) has already been called before, undefined behavior occurs.
 *  If ptr is NULL, no operation is per‐formed.
 * */
void ft_free(void *ptr) {
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
        _chk_dealloc(chk);

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
        _chk_dealloc(chk);

        /* clear the memory block if no chunks is present... */
        if (!_blk_getalloc(blk)) {
            _blk_dealloc(blk);

            /* set the g_info's block to null... */
            g_info.blk.b_sml = 0;
        }
    }

    /* perform large deallocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {
        /* dealloc for the head... */
        if (chk == g_info.blk.b_lrg) {
            /* save the next element from head... */
            chk = chk->c_nxt;

            /* unmap current head... */
            munmap(g_info.blk.b_lrg, sizeof(struct s_mallocChunk) + chk->c_siz);

            /* assign new head (if current 'chk' is null then we effectively clear-out the chunk list)... */
            g_info.blk.b_lrg = chk;
        }

        /* dealloc non-head element... */
        else {
            /* dealloc the tail... */
            if (!chk->c_nxt) {
                munmap(chk, sizeof(struct s_mallocChunk) + chk->c_siz);
            }

            /* dealloc inner element... */
            else {
                /* TODO:
                 *  figure out how to dealloc inner element
                 * */
            }
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


static int _chk_dealloc(struct s_mallocChunk *chk) {
    if (!chk) { return (0); }

    chk->c_dat = ft_memset(chk->c_dat, 0, chk->c_siz);
    chk->c_use = 0;
    return (0);
}
