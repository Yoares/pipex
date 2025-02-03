CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROG    = pipex

SRCS    = pipex.c helper.c free.c
OBJS    = $(SRCS:.c=.o)

HEADER  = pipex.h

LIBFT_A = libft/libft.a

all: $(PROG)


$(PROG): $(OBJS) 
	@cd libft && make && make clean
	$(CC) $(CFLAGS) $(OBJS)  $(LIBFT_A) -o $(PROG)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(PROG) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re 