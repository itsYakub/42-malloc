#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_malloc_h_)
# define _malloc_h_ 1
#
# include <pthread.h>       /* libpthread...    */
# include <unistd.h>        /* sysconf          */
# include <sys/mman.h>      /* mmap, munmap     */
# include <sys/time.h>
# include <sys/resource.h>  /* getrlimit        */
#
# include "./libft/libft.h" /* libft...         */

void free(void *);

void *malloc(size_t);

void *realloc(void *, size_t);

void show_alloc_mem(void);

#endif /* _malloc_h_ */
