#include <stdio.h>

#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

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
                if (chk->c_use) {
                    total += chk->c_siz;
                }

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
                if (chk->c_use) {
                    total += chk->c_siz;
                }

                chk = chk->c_nxt;
            }
            blk = blk->b_nxt;
        }
    }
    
    /* SMALL blocks... */
    if (g_info.blk.b_lrg) {
        ft_putendl_fd("LARGE blocks:", 1);
        /* iterate over every block... */
        struct s_mallocChunk *chk = g_info.blk.b_lrg;
        while (chk) {
            if (chk->c_use) {
                total += chk->c_siz;
            }

            chk = chk->c_nxt;
        }
    }

    ft_putstr_fd("Total: ", 1);
    ft_putnbr_fd(total, 1);
    ft_putchar_fd('\n', 1);
}
