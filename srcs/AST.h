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

void	set_start_end(t_ast **ast, t_token *start, t_token *end);
void	set_cmds_redirs(t_ast **ast, t_token *start, t_token *end);

t_token	*get_center(t_ast *ast, t_token *start, t_token *end);
t_ast	*init_ast(t_token *tokens)
void	generate_ast(t_ast **ast, t_token *start, t_token *end);
void	syntax_error_parser(char *string, t_token **list)

#endif
