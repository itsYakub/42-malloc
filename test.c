#include <time.h>
#include <stdio.h>

#if defined (TEST_LIBFT)
# include "ft_malloc.h"
#else
# include <stdlib.h>

/* libc doesn't provide such function as 'show_alloc_mem' so we must provide something to make the compiler work */
static void show_alloc_mem(void) { }

#endif

int main(void) {
    /* tiny allocs... */
    void *a = malloc(4);
    void *b = malloc(9);
    
    /* small allocs... */
    void *c = malloc(42);
    void *d = malloc(96);
    
    /* large allocs... */
    void *e = malloc(80085);
    
    show_alloc_mem();

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    
    show_alloc_mem();
    
    return (0);
}
