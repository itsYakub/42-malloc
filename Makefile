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
SRCS	= ./ft_malloc.c

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


.PHONY : clean

clean :
	make -C $(LIBFT) clean
	rm -f $(OBJS)

# ========

$(TARGET) : $(OBJS)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS) $(LFLAGS)
	-ln -s $@ libft_malloc.so


$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) -fpic -o $@ -c $<


# ========
