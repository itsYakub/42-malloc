#include <stdio.h>

#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

void show_alloc_mem(void) {
    size_t total = 0;

    /* TINY blocks... */
    if (g_info.blk.b_tny) {
        ft_putendl_fd("TINY blocks:", 1);
        /* iterate over every block... */
        struct s_mallocBlock *blk = g_info.blk.b_tny;
        for (size_t i = 1; blk; i++, blk = blk->b_nxt) {
            printf("%zu : %p :\n", i, blk);

            /* iterate over every chunk... */
            struct s_mallocChunk *chk = blk->b_dat;
            while (chk) {
                if (chk->c_use) {
                    printf("- %p - %p : %zu bytes\n", chk->c_dat, chk->c_nxt, chk->c_siz);
                    total += chk->c_siz;
                }

                chk = chk->c_nxt;
            }
        }
    }
    
    /* SMALL blocks... */
    if (g_info.blk.b_sml) {
        ft_putendl_fd("SMALL blocks:", 1);
        /* iterate over every block... */
        struct s_mallocBlock *blk = g_info.blk.b_sml;
        for (size_t i = 1; blk; i++, blk = blk->b_nxt) {
            printf("%zu : %p :\n", i, blk);

            /* iterate over every chunk... */
            struct s_mallocChunk *chk = blk->b_dat;
            while (chk) {
                if (chk->c_use) {
                    printf("- %p - %p : %zu bytes\n", chk->c_dat, chk->c_nxt, chk->c_siz);
                    total += chk->c_siz;
                }

                chk = chk->c_nxt;
            }
        }
    }
    
    /* SMALL blocks... */
    if (g_info.blk.b_lrg) {
        ft_putendl_fd("LARGE blocks:", 1);
        /* iterate over every block... */
        struct s_mallocChunk *chk = g_info.blk.b_lrg;
        while (chk) {
            if (chk->c_use) {
                printf("- %p - %p : %zu bytes\n", chk->c_dat, chk->c_dat + chk->c_siz, chk->c_siz);
                total += chk->c_siz;
            }

            chk = chk->c_nxt;
        }
    }

    printf("Total: %zu bytes\n", total);
}
