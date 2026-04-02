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
    srand(time(0));
    for (size_t i = 1; i <= 64; i++) {
        int *ptr = malloc(sizeof(int) * i);
        if (!ptr) {
            return (1);
        }

        *ptr = i;
        // printf("%p = %d\n", ptr, *ptr);

        if (rand() % 2) { free(ptr); }
    }
    show_alloc_mem();
    
    return (0);
}
