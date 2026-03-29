#include <stdio.h>
#include "ft_malloc.h"

int main(void) {
    int *arr = malloc(sizeof(int));
    if (!arr) {
        return (1);
    }

    *arr = 42;
    printf("%p = %d\n", arr, *arr);
    free(arr);

    return (0);
}
