#include "./ft_malloc.h"
#include "./ft_malloc_int.h"

/* realloc:
 *  The realloc() function changes the size of the memory block pointed to by ptr to size bytes.
 *  The contents  will  be  unchanged  in  the range  from  the start of the region up to the minimum of the old and new sizes.
 *  If the new size is larger than the old size, the added memory will not be initialized.
 *  If ptr is NULL, then the call is equivalent to malloc(size), for all values of size;
 *  if size  is  equal to zero, and ptr is not NULL, then the call is equivalent to free(ptr).
 *  Unless ptr is NULL, it must have been returned by an earlier call to malloc(), calloc(), or realloc().
 *  If the area pointed to was moved, a free(ptr) is done.
 * */
void *realloc(void *ptr, size_t size) {
    /* Allocate the new memory block... */
    void *newptr = malloc(size);
    if (!newptr) {
        return (0);
    }

    /* Check if 'ptr' is null - if so, return the new block... */
    if (!ptr) { return (newptr); }

    ptr = (char *) ptr - sizeof(struct s_mallocChunk);
    
    /* Get the allocs chunk to get the size of the allocated block... */
    struct s_mallocChunk *chk = (struct s_mallocChunk *) ptr;

    /* copy all the possible bytes from the 'ptr' to the 'newptr'... */
    newptr = ft_memcpy(newptr, chk->c_dat, chk->c_siz);
    if (!newptr) {
        return (0);
    }

    /* release old 'ptr'... */
    free(chk->c_dat);

    /* return 'newptr'... */
    return (newptr);
}
