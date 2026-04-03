#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_malloc_int_h_)
# define _malloc_int_h_ 1
#
# include "./ft_malloc.h" 
#
# /* FT_MALLOC_TINY_SIZE - small of a singular "tiny" allocation */
# if !defined (FT_MALLOC_TINY_SIZE)
#  define FT_MALLOC_TINY_SIZE 16
# endif /* FT_MALLOC_TINY_SIZE */
#
# /* FT_MALLOC_SMALL_SIZE - small of a singular "small" allocation */
# if !defined (FT_MALLOC_SMALL_SIZE)
#  define FT_MALLOC_SMALL_SIZE 128
# endif /* FT_MALLOC_SMALL_SIZE */

/* SECTION: malloc info
 * */

struct s_mallocChunk {
    
    void *c_nxt;    /* c_nxt - next available block */

    void *c_blk;    /* c_blk - parent block of the chunk */

    void *c_dat;    /* c_dat - chunk's memory */

    size_t c_siz;   /* c_siz - chunk's size */

    bool c_use;     /* c_use - flag if chunk is used */

};


struct s_mallocBlock {
    
    struct s_mallocBlock *b_nxt;

    struct s_mallocBlock *b_prv;

    size_t b_siz;

    size_t b_cap;

    void *b_dat;

};


struct s_mallocInfo {
    
    struct {

        struct s_mallocBlock *b_tny;

        struct s_mallocBlock *b_sml;

        struct s_mallocChunk *b_lrg;
        
    } blk;

    /* TODO:
     *  Implement multthreading - safety
     * */
    struct {
        
        pthread_mutex_t p_mtx;

    } pthr;

};

extern struct s_mallocInfo g_info;

#endif /* _malloc_int_h_ */
