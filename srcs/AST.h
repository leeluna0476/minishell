#ifndef AST_H
# define AST_H

#include "parse_struct.h"

typedef struct s_ast t_ast;

struct s_ast
{
	enum e_type		type;
	t_token			*start;
	t_token			*end;
	char			*error;
	struct s_ast	*left;
	struct s_ast	*right;
};

int	is_redirection(t_type type);
void	print_ast(t_ast *ast);
void	free_node(t_ast **node);
void	free_ast(t_ast **ast);

void	check_center_error(t_ast *ast, t_token *center);
int	check_redirection_error(t_ast *ast, t_token *node);
int	check_error(t_ast *ast);

int	get_bracket_flag(t_token **start, t_token **end, \
					t_token **first, t_token **last);
t_token	*check_bracket(t_token *start, t_token *end);
int	check_if_single_pair(t_token *start, t_token *end);
void	remove_bracket(t_token **start, t_token **end);
t_token	*check_pipe_in_bracket(t_token *start, t_token *end);
void	set_start_end(t_ast **ast, t_token *start, t_token *end);

t_token	*get_center(t_ast *ast, t_token *start, t_token *end);
t_ast	*init_ast(t_token *tokens);
void	generate_ast(t_ast **ast, t_token *start, t_token *end);
void	syntax_error_parser(char *string, t_token **list);

#endif
