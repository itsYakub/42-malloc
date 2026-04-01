#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static void *_blk_alloc(const size_t);

static void *_blk_getchk(struct s_mallocBlock *, const size_t);

static void *_chk_alloc(struct s_mallocBlock *, const size_t, const size_t);

/* malloc:
 *  The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.
 *  If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
 * */
void *ft_malloc(size_t size) {
    if (!size) { return (0); }

    void *ptr = 0;

    /* perform tiny allocation... */
    if (size > 0 && size <= FT_MALLOC_TINY_SIZE) {
        if (!g_info.blk.b_tny) {
            g_info.blk.b_tny = _blk_alloc(FT_MALLOC_TINY_SIZE);
        }
    
        ptr = _chk_alloc(g_info.blk.b_tny, FT_MALLOC_TINY_SIZE, size);
        if (!ptr) {
            return (0);
        }
    }

    /* perform small allocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
        if (!g_info.blk.b_sml) {
            g_info.blk.b_sml = _blk_alloc(FT_MALLOC_SMALL_SIZE);
        }
        
        ptr = _chk_alloc(g_info.blk.b_sml, FT_MALLOC_SMALL_SIZE, size);
        if (!ptr) {
            return (0);
        }
    }

    /* perform large allocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {

    }

    return (ptr);
}


static void *_blk_alloc(const size_t cap) {
    /* alloc the new block... */
    size_t siz = sizeof(struct s_mallocBlock) + 100 * (sizeof(struct s_mallocChunk) + cap);
    void *addr = mmap(0, siz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (!addr) {
        return (0);
    }

    /* clear allocated block...  */
    addr = ft_memset(addr, 0, siz);

    /* configure block metadata... */
    struct s_mallocBlock *blk = (struct s_mallocBlock *) addr;
    blk->b_siz = 0;
    blk->b_cap = 100 * cap; 
    blk->b_dat = (char * ) blk + sizeof(struct s_mallocBlock);

    return (blk);
}


static void *_blk_getchk(struct s_mallocBlock *blk, const size_t siz) {
    /* null-check... */
    if (!blk) { return (0); }

    /* iterate over the block to find free chunk... */
    struct s_mallocChunk *chk = blk->b_dat;
    for (size_t i = (void *) chk - blk->b_dat; i < blk->b_cap; i = (void *) chk - blk->b_dat) {
        /* case: last chunk... */
        if (!chk->c_nxt) {
            /* check if we even have enough room for a new data... */
            if ((i + sizeof(struct s_mallocChunk)) + siz < blk->b_cap) {
                return (chk);
            }

            /* otherwise break from the loop...*/
            break;
        }

        /* case: chunk inside... */
        else if (chk->c_siz <= siz) {
            if (!chk->c_use) {
                return (chk);
            }
        }

        /* move to the next chunk... */
        chk = chk->c_nxt;
    }

    /* free chunk not found, return null... */
    return (0);
}


static void *_chk_alloc(struct s_mallocBlock *blk, const size_t cap, const size_t size) {
    /* check if current block was exhausted... */
    struct s_mallocChunk *chk = 0;
    while (!(chk = _blk_getchk(blk, size))) {
        if (!blk->b_nxt) {
            blk->b_nxt = _blk_alloc(cap);
            if (!blk) {
                return (0);
            }
        
            blk->b_nxt->b_prv = blk;
        }
        
        blk = blk->b_nxt;
    }

    /* set the current chunk metadata... */
    chk->c_blk = blk;
    chk->c_dat = (char *) chk + sizeof(struct s_mallocChunk);
    chk->c_nxt = (char *) chk + sizeof(struct s_mallocChunk) + size;
    chk->c_siz = size;
    chk->c_use = 1;

    /* update block's metadata... */
    blk->b_siz += size;

    /* return new poitner... */
    return (chk->c_dat);
}

/* SECTION: s_mallocInfo...
 * */

struct s_mallocInfo g_info = {
    .blk = {
        .b_tny = 0,
        .b_sml = 0
    }
};
