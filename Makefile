NAME=minishell
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3 -I $(HEADERS_DIR)
RM=rm -fr
SRCS_DIR=./srcs/
HEADERS_DIR=./includes/
SRCS=$(SRCS_DIR)center.c $(SRCS_DIR)error.c $(SRCS_DIR)get_token.c $(SRCS_DIR)ast.c $(SRCS_DIR)ast_utils.c $(SRCS_DIR)check_ast_error.c $(SRCS_DIR)meta.c $(SRCS_DIR)set_nodes.c $(SRCS_DIR)token_utils.c $(SRCS_DIR)tokenizer.c $(SRCS_DIR)testmain.c $(SRCS_DIR)bracket.c $(SRCS_DIR)signal.c
HEADERS=$(HEADERS_DIR)parse_define.h $(HEADERS_DIR)parse_struct.h $(HEADERS_DIR)tokenizer.h $(HEADERS_DIR)parser.h $(HEADERS_DIR)signal_handler.h
OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lft -L./libft/ -lreadline

$(OBJS): $(SRCS) $(HEADERS)

clean:
	make clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
