#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_malloc_h_)
# define _malloc_h_ 1
#
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
#
# include <errno.h>
# include <pthread.h>       /* libpthread...    */
# include <unistd.h>        /* sysconf          */
#
# include <sys/mman.h>      /* mmap, munmap     */
# include <sys/time.h>
# include <sys/resource.h>  /* getrlimit        */
#
# include "./libft/libft.h" /* libft...         */

void ft_free(void *);

void *ft_malloc(size_t);

void *ft_realloc(void *, size_t);

void show_alloc_mem(void);

# define free       ft_free     /* define 'ft_free' as current 'free' */
# define malloc     ft_malloc   /* define 'ft_malloc' as current 'malloc' */
# define realloc    ft_realloc  /* define 'ft_realloc' as current 'realloc' */
#
#endif /* _malloc_h_ */
