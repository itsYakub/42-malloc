#include <time.h>
#include <stdio.h>

#if defined (TEST_LIBFT)
# include "ft_malloc.h"
#else
# include <stdlib.h>
#
# include "./libft/libft.h"

/* libc doesn't provide such function as 'show_alloc_mem' so we must provide something to make the compiler work */
static void show_alloc_mem(void) { }

#endif

int main(void) {
    ft_putendl_fd("=== TEST 1 ===", 1);

    void *ptrs[] = {
        /* tiny allocs... */
        malloc(1),
        malloc(4),
        malloc(16),
    
        /* small allocs... */
        malloc(42),
        malloc(69),
        malloc(96),

        /* large allocs... */
        malloc(129),
        malloc(420),
        malloc(1337),
        malloc(2137),
        malloc(80085)
    };

    show_alloc_mem();
    
    for (int i = sizeof(ptrs) / sizeof(void *) - 1; i >= 0; i--) {
        free(ptrs[i]);
    }
    
    show_alloc_mem();
    
    ft_putendl_fd("=== TEST 2 ===", 1);

    char *ptr = malloc(8);
    ft_strlcpy(ptr, "Hello", 8);
    ft_putendl_fd(ptr, 1);

    show_alloc_mem();

    ptr = realloc(ptr, 16);
    ft_strlcat(ptr, ", World!", 16);
    ft_putendl_fd(ptr, 1);

    show_alloc_mem();
   
    free(ptr);
    
    show_alloc_mem();
    
    ft_putendl_fd("=== TEST 3 ===", 1);

    void *a = malloc(4);
    void *b = malloc(8);
    free(a);
    void *c = malloc(4);
    
    show_alloc_mem();

    free(b);
    free(c);
    
    show_alloc_mem();

    return (0);
}
