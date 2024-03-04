#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

#-------------------------------------------

NAME = minishell
CC = cc
CFLAGS = -I./includes -Wall -Wextra -Werror
LINKING_FLAG = -lft -L./srcs/libft/ -lreadline
MAN_SRCS = ./srcs/envs/build_env_pack.c \
		./srcs/envs/env_utils.c \
		./srcs/execute/execute.c \
		./srcs/execute/execute_utils.c \
		./srcs/execute/execute_utils2.c \
		./srcs/execute/pipe_utils.c \
		./srcs/execute/utils.c \
		./srcs/execute/utils2.c \
		./srcs/execute/redirections/redirections.c \
		./srcs/execute/redirections/redir_utils.c \
		./srcs/execute/redirections/do_heredoc.c \
		./srcs/execute/redirections/heredoc_utils.c \
		./srcs/expand/expand.c \
		./srcs/expand/do_expand.c \
		./srcs/expand/expand_utils.c \
		./srcs/expand/wildcard.c \
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
		./srcs/testmain.c
MAN_OBJS = $(MAN_SRCS:.c=.o)

BONUS_SRCS = ./srcs/envs/build_env_pack_bonus.c \
		./srcs/envs/env_utils_bonus.c \
		./srcs/execute/execute_bonus.c \
		./srcs/execute/execute_utils_bonus.c \
		./srcs/execute/execute_utils2_bonus.c \
		./srcs/execute/pipe_utils_bonus.c \
		./srcs/execute/utils_bonus.c \
		./srcs/execute/utils2_bonus.c \
		./srcs/execute/redirections/redirections_bonus.c \
		./srcs/execute/redirections/redir_utils_bonus.c \
		./srcs/execute/redirections/do_heredoc_bonus.c \
		./srcs/execute/redirections/heredoc_utils_bonus.c \
		./srcs/expand/expand_bonus.c \
		./srcs/expand/do_expand_bonus.c \
		./srcs/expand/expand_utils_bonus.c \
		./srcs/expand/wildcard_bonus.c \
		./srcs/expand/wildcard_utils_bonus.c \
		./srcs/builtins/builtin_exec_bonus.c \
		./srcs/builtins/builtin_utils_bonus.c \
		./srcs/builtins/do_builtin_bonus.c \
		./srcs/builtins/do_builtin2_bonus.c \
		./srcs/parse/ast_bonus.c \
		./srcs/parse/ast_utils_bonus.c \
		./srcs/parse/bracket_bonus.c \
		./srcs/parse/center_bonus.c \
		./srcs/parse/check_ast_error_bonus.c \
		./srcs/parse/error_bonus.c \
		./srcs/parse/get_token_bonus.c \
		./srcs/parse/meta_bonus.c \
		./srcs/parse/set_nodes_bonus.c \
		./srcs/parse/token_utils_bonus.c \
		./srcs/parse/tokenizer_bonus.c \
		./srcs/signal/signal_bonus.c \
		./srcs/testmain_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT = ./srcs/libft/libft.a

ifeq ($(MAKECMDGOALS),bonus)
	OBJS=$(BONUS_OBJS)
else
	OBJS=$(MAN_OBJS)
endif

all : $(NAME)
bonus : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@echo $(GREEN)"---building minishell"
	@$(CC) $(CFLAGS) $(LINKING_FLAG) -o $(NAME) $^
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	@echo $(YELLOW)"                    MINISHELL IS READY"$(EOC)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)

$(LIBFT) :
	@echo $(GREEN)"---creating libft.a"$(EOF)
	@cd ./srcs/libft ; $(MAKE)
#	@echo $(LINE_CLEAR)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo $(GREEN)"---make libft clean"$(EOC)
	@make clean -C srcs/libft
	@echo $(GREEN)"---make clean"$(EOC)
	@rm -fr $(OBJS)

fclean : clean
	@echo $(GREEN)"---make libft fclean"$(EOC)
	@make fclean -C srcs/libft
	@echo $(GREEN)"---make fclean"$(EOC)
	@rm -fr $(NAME)

re :
	@echo $(GREEN)"---make re"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all bonus clean fclean re
