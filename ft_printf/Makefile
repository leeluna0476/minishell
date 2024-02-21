CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./ft_printf.c ft_printf2.c
M_OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

all : $(NAME)

$(NAME) : $(M_OBJS)
	ar -rc $@ $^

clean :
	rm -f $(M_OBJS)

fclean : clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all clean fclean re