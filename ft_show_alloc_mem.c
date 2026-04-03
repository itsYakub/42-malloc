#include <stdio.h>

#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

static void _chk_printptr(struct s_mallocChunk *);

/* TODO:
 *  Custom numeric logger functions for printing pointers...
 * */
void show_alloc_mem(void) {
    size_t total = 0;

    /* TINY blocks... */
    if (g_info.blk.b_tny) {
        ft_putendl_fd("TINY blocks:", 1);
        /* iterate over every block... */
        struct s_mallocBlock *blk = g_info.blk.b_tny;
        while (blk) {
            /* iterate over every chunk... */
            struct s_mallocChunk *chk = blk->b_dat;
            while (chk) {
                total += chk->c_siz;
                
                _chk_printptr(chk);
                chk = chk->c_nxt;
            }
            blk = blk->b_nxt;
        }
    }
    
    /* SMALL blocks... */
    if (g_info.blk.b_sml) {
        ft_putendl_fd("SMALL blocks:", 1);
        /* iterate over every block... */
        struct s_mallocBlock *blk = g_info.blk.b_sml;
        while (blk) {
            /* iterate over every chunk... */
            struct s_mallocChunk *chk = blk->b_dat;
            while (chk) {
                total += chk->c_siz;
                    
                _chk_printptr(chk);
                chk = chk->c_nxt;
            }
            blk = blk->b_nxt;
        }
    }
    
    /* LARGE blocks... */
    if (g_info.blk.b_lrg) {
        ft_putendl_fd("LARGE blocks:", 1);
        /* iterate over every block... */
        struct s_mallocChunk *chk = g_info.blk.b_lrg;
        while (chk) {
            total += chk->c_siz;

            _chk_printptr(chk);
            chk = chk->c_nxt;
        }
    }

    if (!total) { return; }
    ft_putstr_fd("Total: ", 1);
    ft_putnbr_fd(total, 1);
    ft_putchar_fd('\n', 1);
}


static void _chk_printptr(struct s_mallocChunk *chk) {
    if (!chk)        { return; }
    if (!chk->c_siz) { return; }
    
    size_t start = (uintptr_t) chk->c_dat,
           end   = (uintptr_t) chk->c_dat + chk->c_siz;

    ft_putstr_fd("- 0x", 1);
    ft_putnbr_base_fd(start, 16, 1);
    ft_putstr_fd(" - 0x", 1);
    ft_putnbr_base_fd(end, 16, 1);
    ft_putstr_fd(" : ", 1);
    ft_putnbr_fd(chk->c_siz, 1);
    ft_putendl_fd(" bytes", 1);
}
