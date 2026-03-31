#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static void *_blk_alloc(const size_t);

static void *_blk_getchk(struct s_mallocBlock *);

/* malloc:
 *  The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.
 *  If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
 * */
void *malloc(size_t size) {
    if (!size) { return (0); }

    void *ptr = 0;

    /* perform tiny allocation... */
    if (size > 0 && size <= FT_MALLOC_TINY_SIZE) {
        /* check if block is null... */
        struct s_mallocBlock *blk = 0;
        if (!g_info.blk.b_tny) {
            g_info.blk.b_tny = _blk_alloc(FT_MALLOC_TINY_SIZE);
            if (!g_info.blk.b_tny) {
                return (0);
            }
        }
        blk = g_info.blk.b_tny;

        /* check the size of the memory block... */
        struct s_mallocChunk *chk = 0;
        while (!(chk = _blk_getchk(blk))) {
            if (!blk->b_nxt) {
                blk->b_nxt = _blk_alloc(FT_MALLOC_TINY_SIZE);
                if (!blk) {
                    return (0);
                }
            
                blk->b_nxt->b_prv = blk;
            }
            
            blk = blk->b_nxt;
        }

        /* and lastly, assign the 'ptr'... */
        ptr = chk->c_dat;
        chk->c_siz = size;
        chk->c_use = 1;
    }

    /* perform small allocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
    
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
    blk->b_siz = siz;
    blk->b_cap = siz - sizeof(struct s_mallocBlock);
    blk->b_dat = (char * ) blk + sizeof(struct s_mallocBlock);

    /* initialize each chunk... */
    struct s_mallocChunk *chk = blk->b_dat;
    for (size_t i = 0; i < 100; i++) {
        /* configure chunk's metadata... */
        chk->c_blk = blk;
        chk->c_dat = (char *) chk + sizeof(struct s_mallocChunk);
        chk->c_nxt = (char *) chk->c_dat + cap;

        /* move chunk's pointer to the next chunk... */
        chk = chk->c_nxt;
    }

    return (blk);
}


static void *_blk_getchk(struct s_mallocBlock *blk) {
    /* null-check... */
    if (!blk) { return (0); }

    /* iterate over the block to find free chunk... */
    struct s_mallocChunk *chk = blk->b_dat;
    for (size_t i = 0; i < 100; i++) {
        /* free chunk found, return it... */
        if (!chk->c_use) {
            return (chk);
        }

        chk = chk->c_nxt;
    }

    /* free chunk not found, return null... */
    return (0);
}

/* SECTION: s_mallocInfo...
 * */

struct s_mallocInfo g_info = {
    .blk = {
        .b_tny = 0,
        .b_sml = 0
    }
};
