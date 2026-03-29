#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_malloc_h_)
# define _malloc_h_ 1
#
# include <pthread.h>       /* libpthread... */
# include <unistd.h>        /* getpagesize */
# include <sys/mman.h>      /* mmap, munmap */
# include <sys/time.h>
# include <sys/resource.h>  /* getrlimit */
#
# include "./libft/libft.h" /* libft... */

#endif /* _malloc_h_ */
