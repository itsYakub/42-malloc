#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static struct s_mallocBlock *_malloc_blkalloc(const size_t);

/* malloc:
 *  The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.
 *  If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
 * */
void *malloc(size_t size) {
    if (!size) { return (0); }

    void *ptr = 0;

    /* perform tiny allocation... */
    if (size > 0 && size <= FT_MALLOC_TINY_SIZE) {
        struct s_mallocBlock *blk = 0;

        /* check if block is null... */
        if (!g_info.blk.b_tny) {
            blk = g_info.blk.b_tny = _malloc_blkalloc(FT_MALLOC_TINY_SIZE);
            if (!blk) {
                return (0);
            }
        }
        else {
            blk = g_info.blk.b_tny;
        }

        /* check the size of the memory block... */
        size_t c_siz = size + sizeof(struct s_mallocHeader);
        while (blk->b_siz + c_siz >= blk->b_cap) {
            if (!blk->b_nxt) {
                blk->b_nxt = _malloc_blkalloc(FT_MALLOC_TINY_SIZE);
                if (!blk) {
                    return (0);
                }
            
                blk->b_nxt->b_prv = blk;
            }
            
            blk = blk->b_nxt;
        }

        /* now, get the memory chunk... */
        struct s_mallocHeader *header = (struct s_mallocHeader *) ((char *) blk->b_dat + blk->b_siz);
        header->h_blk = blk;
        header->h_dat = header + sizeof(struct s_mallocHeader);
        header->h_siz = c_siz;

        /* increment the size of the block... */
        blk->b_siz += c_siz;

        /* and lastly, assign the 'ptr'... */
        ptr = header->h_dat;
    }

    /* perform small allocation... */
    else if (size > FT_MALLOC_TINY_SIZE && size <= FT_MALLOC_SMALL_SIZE) {
        struct s_mallocBlock *blk = 0;

        /* check if block is null... */
        if (!g_info.blk.b_sml) {
            blk = g_info.blk.b_sml = _malloc_blkalloc(FT_MALLOC_SMALL_SIZE);
            if (!blk) {
                return (0);
            }
        }
        else {
            blk = g_info.blk.b_sml;
        }

        /* check the size of the memory block... */
        size_t c_siz = size + sizeof(struct s_mallocHeader);
        while (blk->b_siz + c_siz >= blk->b_cap) {
            if (!blk->b_nxt) {
                blk->b_nxt = _malloc_blkalloc(FT_MALLOC_SMALL_SIZE);
                if (!blk) {
                    return (0);
                }
            
                blk->b_nxt->b_prv = blk;
            }
            
            blk = blk->b_nxt;
        }

        /* now, get the memory chunk... */
        struct s_mallocHeader *header = (struct s_mallocHeader *) ((char *) blk->b_dat + blk->b_siz);
        header->h_blk = blk;
        header->h_dat = header + sizeof(struct s_mallocHeader);
        header->h_siz = c_siz;

        /* increment the size of the block... */
        blk->b_siz += c_siz;

        /* and lastly, assign the 'ptr'... */
        ptr = header->h_dat;
    }

    /* perform large allocation... */
    else if (size > FT_MALLOC_SMALL_SIZE) {
        /* allocate new "lerge" chunk... */
        void *addr = mmap(0, sizeof(struct s_mallocHeader) + size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (!addr) {
            return (0);
        }

        /* initialize chunk's header... */
        struct s_mallocHeader *header = addr;
        header->h_blk = 0;
        header->h_dat = addr + sizeof(struct s_mallocHeader);
        header->h_siz = size;
        
        /* assign the value of 'ptr'... */
        ptr = header->h_dat;
    }

    return (ptr);
}


static struct s_mallocBlock *_malloc_blkalloc(const size_t cap) {
    /* alloc and clear the new block...
     * */
    struct s_mallocBlock *blk = mmap(0, sizeof(struct s_mallocBlock), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (!blk) {
        return (0);
    }

    blk = ft_memset(blk, 0, sizeof(struct s_mallocBlock));

    /* setup block data...
     * */
    blk->b_cap = (sizeof(struct s_mallocHeader) + cap) * 100;
    blk->b_dat = mmap(0, blk->b_cap, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (!blk->b_dat) {
        /* preserve errno... */
        int err = errno;

        /* release the block... */
        munmap(blk, sizeof(struct s_mallocBlock));

        /* revert errno */
        errno = err;

        return (0);
    }

    return (blk);
}

/* SECTION: s_mallocInfo...
 * */

struct s_mallocInfo g_info = {
    .blk = {
        .b_tny = 0,
        .b_sml = 0
    }
};
