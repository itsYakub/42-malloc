#include <stdio.h>
#include "ft_malloc.h"

int main(void) {
    for (size_t i = 1; i <= 16; i++) {
        int *ptr = malloc(sizeof(int) * i);
        if (!ptr) {
            return (1);
        }

        *ptr = i;
        printf("%p = %d\n", ptr, *ptr);
    }
    return (0);
}
