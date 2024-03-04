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
MAN_SRCS = ./srcs/mandatory/envs/build_env_pack.c \
		./srcs/mandatory/envs/env_utils.c \
		./srcs/mandatory/execute/execute.c \
		./srcs/mandatory/execute/execute_utils.c \
		./srcs/mandatory/execute/execute_utils2.c \
		./srcs/mandatory/execute/pipe_utils.c \
		./srcs/mandatory/execute/utils.c \
		./srcs/mandatory/execute/utils2.c \
		./srcs/mandatory/execute/redirections/redirections.c \
		./srcs/mandatory/execute/redirections/redir_utils.c \
		./srcs/mandatory/execute/redirections/do_heredoc.c \
		./srcs/mandatory/execute/redirections/heredoc_utils.c \
		./srcs/mandatory/expand/expand.c \
		./srcs/mandatory/expand/do_expand.c \
		./srcs/mandatory/expand/expand_utils.c \
		./srcs/mandatory/expand/wildcard.c \
		./srcs/mandatory/expand/wildcard_utils.c \
		./srcs/mandatory/builtins/builtin_exec.c \
		./srcs/mandatory/builtins/builtin_utils.c \
		./srcs/mandatory/builtins/do_builtin.c \
		./srcs/mandatory/builtins/do_builtin2.c \
		./srcs/mandatory/parse/ast.c \
		./srcs/mandatory/parse/ast_utils.c \
		./srcs/mandatory/parse/bracket.c \
		./srcs/mandatory/parse/center.c \
		./srcs/mandatory/parse/check_ast_error.c \
		./srcs/mandatory/parse/error.c \
		./srcs/mandatory/parse/get_token.c \
		./srcs/mandatory/parse/meta.c \
		./srcs/mandatory/parse/set_nodes.c \
		./srcs/mandatory/parse/token_utils.c \
		./srcs/mandatory/parse/tokenizer.c \
		./srcs/mandatory/signal/signal.c \
		./srcs/mandatory/main.c
MAN_OBJS = $(MAN_SRCS:.c=.o)

BONUS_SRCS = ./srcs/bonus/envs/build_env_pack_bonus.c \
		./srcs/bonus/envs/env_utils_bonus.c \
		./srcs/bonus/execute/execute_bonus.c \
		./srcs/bonus/execute/execute_utils_bonus.c \
		./srcs/bonus/execute/execute_utils2_bonus.c \
		./srcs/bonus/execute/pipe_utils_bonus.c \
		./srcs/bonus/execute/utils_bonus.c \
		./srcs/bonus/execute/utils2_bonus.c \
		./srcs/bonus/execute/redirections/redirections_bonus.c \
		./srcs/bonus/execute/redirections/redir_utils_bonus.c \
		./srcs/bonus/execute/redirections/do_heredoc_bonus.c \
		./srcs/bonus/execute/redirections/heredoc_utils_bonus.c \
		./srcs/bonus/expand/expand_bonus.c \
		./srcs/bonus/expand/do_expand_bonus.c \
		./srcs/bonus/expand/expand_utils_bonus.c \
		./srcs/bonus/expand/wildcard_bonus.c \
		./srcs/bonus/expand/wildcard_utils_bonus.c \
		./srcs/bonus/builtins/builtin_exec_bonus.c \
		./srcs/bonus/builtins/builtin_utils_bonus.c \
		./srcs/bonus/builtins/do_builtin_bonus.c \
		./srcs/bonus/builtins/do_builtin2_bonus.c \
		./srcs/bonus/parse/ast_bonus.c \
		./srcs/bonus/parse/ast_utils_bonus.c \
		./srcs/bonus/parse/bracket_bonus.c \
		./srcs/bonus/parse/center_bonus.c \
		./srcs/bonus/parse/check_ast_error_bonus.c \
		./srcs/bonus/parse/error_bonus.c \
		./srcs/bonus/parse/get_token_bonus.c \
		./srcs/bonus/parse/meta_bonus.c \
		./srcs/bonus/parse/set_nodes_bonus.c \
		./srcs/bonus/parse/token_utils_bonus.c \
		./srcs/bonus/parse/tokenizer_bonus.c \
		./srcs/bonus/signal/signal_bonus.c \
		./srcs/bonus/main_bonus.c
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

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo $(GREEN)"---make libft clean"$(EOC)
	@make clean -C srcs/libft
	@echo $(GREEN)"---make clean"$(EOC)
	@rm -fr $(MAN_OBJS) $(BONUS_OBJS)

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
