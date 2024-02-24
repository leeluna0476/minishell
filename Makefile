NAME=minishell
CC=cc
RM=rm -fr
HEADERS_DIR=./includes/
CFLAGS=-Wextra -Wall -Werror -g -I./includes

SRCS = ./srcs/envs/build_env_pack.c \
		./srcs/envs/env_utils.c \
		./srcs/execute/execute.c \
		./srcs/execute/execute_utils.c \
		./srcs/execute/execute_utils2.c \
		./srcs/execute/pipe_utils.c \
		./srcs/execute/utils.c \
		./srcs/execute/redirections/redirections.c \
		./srcs/execute/redirections/redir_utils.c \
		./srcs/execute/redirections/do_heredoc.c \
		./srcs/expand/expand.c \
		./srcs/expand/do_expand.c \
		./srcs/expand/expand_utils.c \
		./srcs/expand/wildcard_utils.c \
		./srcs/builtins/builtin_exec.c \
		./srcs/builtins/builtin_utils.c \
		./srcs/builtins/do_builtin.c \
		./srcs/builtins/do_builtin2.c \
		./srcs/parse/ast.c \
		./srcs/parse/ast_utils.c \
		./srcs/parse/bracket.c \
		./srcs/parse/center.c \
		./srcs/parse/check_ast_error.c \
		./srcs/parse/error.c \
		./srcs/parse/get_token.c \
		./srcs/parse/meta.c \
		./srcs/parse/set_nodes.c \
		./srcs/parse/token_utils.c \
		./srcs/parse/tokenizer.c \
		./srcs/signal/signal.c \
		./srcs/parse/wildcard.c \
		./srcs/testmain.c


# HEADERS= ./includes/env.h \
# 		 ./includes/utils.h \
# 		 ./includes/expand.h \
# 		 ./includes/parser.h \
# 		 ./includes/builtin.h \
# 		 ./includes/execute.h \
# 		 ./includes/tokenizer.h \
# 		 ./includes/redirection.h \
# 		 ./includes/exec_structures.h

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./srcs/libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lft -L./srcs/libft/ -lreadline

$(OBJS): $(SRCS) $(HEADERS)

clean:
	make clean -C ./srcs/libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./srcs/libft
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
