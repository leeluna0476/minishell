NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3
RM=rm -fr
SRCS=center.c error.c get_token.c ast.c ast_utils.c check_ast_error.c meta.c set_nodes.c token_utils.c tokenizer.c testmain.c bracket.c
HEADERS=parse_struct.h AST.h
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lft -L../libft/ -lreadline

$(OBJS): $(SRCS) $(HEADERS)

clean:
	make clean -C ../libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ../libft
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
