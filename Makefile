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
CFLAGS = -I./includes
# -Wall -Wextra -Werror
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
		./srcs/builtins/builtin_exec.c \
		./srcs/builtins/builtin_utils.c \
		./srcs/builtins/do_builtin.c \
		./srcs/builtins/do_builtin2.c \
		./test_main.c \

OBJS = $(SRCS:.c=.o)
LIBFT = ./srcs/libft/libft.a

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LINKING_FLAG) -o $(NAME) $^
	@echo $(GREEN)"\n==========================================================\n"$(EOC)
	@echo $(YELLOW)"                    MINISHELL IS READY"$(EOC)
	@echo $(GREEN)"\n==========================================================\n"$(EOC)

$(LIBFT) :
	@cd ./srcs/libft ; $(MAKE)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	cd ./srcs/libft ; $(MAKE) clean

fclean : clean
	rm -f $(NAME)
	cd ./srcs/libft ; $(MAKE) fclean

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY : all bonus clean fclean re
