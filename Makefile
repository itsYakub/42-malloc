# ========

SHELL	= /usr/bin/zsh

# ========

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# ========

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -ggdb3 -std=c99
LFLAGS	= -lft
LDFLAGS	= -L$(LIBFT)

# ========

OBJS	= $(SRCS:.c=.o)
SRCS	= ./ft_free.c			\
		  ./ft_malloc.c			\
		  ./ft_realloc.c		\
		  ./ft_show_alloc_mem.c	\

# ========

LIBFT	= ./libft/

# ========

TARGET	= ./libft_malloc_$(HOSTTYPE).so

# ========

.PHONY : all

all : $(TARGET)


.PHONY : re

re : fclean all


.PHONY : fclean

fclean : clean
	make -C $(LIBFT) fclean
	rm -f $(TARGET)
	rm -f libft_malloc.so


.PHONY : clean

clean :
	make -C $(LIBFT) clean
	rm -f $(OBJS)


.PHONY : test

test : all
	-$(CC) $(CFLAGS) -DTEST_LIBFT test.c -o test_libft.out -L. -L./libft -lft -l:$(TARGET)
	-$(CC) $(CFLAGS) -DTEST_LIBC  test.c -o test_libc.out  -L. -L./libft -lft

# ========

$(TARGET) : $(OBJS)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS) $(LFLAGS)
	-ln -fs $@ libft_malloc.so


$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

# ========
