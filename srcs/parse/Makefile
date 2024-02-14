NAME=minishell
CC=cc
//CFLAGS=-Wall -Wextra -Werror
RM=rm -fr
SRCS=ast.c ast_utils.c check_ast_error.c meta.c set_nodes.c token_utils.c tokenizer.c testmain.c ../builtins/builtin_exec.c ../builtins/builtin_utils.c ../builtins/do_builtin.c ../builtins/do_builtin2.c ../envs/env_utils.c ../envs/build_env_pack.c ../expand/expand.c ../expand/do_expand.c ../expand/expand_utils.c ../execute/execute.c ../execute/do_heredoc.c ../execute/redir_utils.c ../execute/redirections.c ../execute/execute_utils.c
HEADERS=parse_struct.h AST.h
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft
	$(CC) -o $(NAME) $(OBJS) -lft -L../libft/ -lreadline

$(OBJS): $(SRCS) $(HEADERS)

clean:
	make clean -C ../libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ../libft
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
