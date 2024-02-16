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

// ast.c
void	generate_ast(t_ast **ast, t_token *start, t_token *end);

// ast_utils.c
int		is_redirection(t_type type);
t_ast	*init_ast(t_token *tokens);
void	print_ast(t_ast *ast);
void	free_node(t_ast **node);
void	free_ast(t_ast **ast);

// bracket.c
int		get_bracket_flag(t_token **start, t_token **end, \
					t_token **first, t_token **last);
t_token	*check_bracket(t_token *start, t_token *end);
int		check_if_single_pair(t_token *start, t_token *end);
void	remove_bracket(t_token **start, t_token **end);
t_token	*check_pipe_in_bracket(t_token *start, t_token *end);

// center.c
t_token	*take_bracket(t_token *curr, t_token *start);
t_token	*get_logical_exp(t_ast *ast, t_token *start, t_token *end);
t_token	*get_pipeline(t_ast *ast, t_token *start, t_token *end);
t_token	*get_center(t_ast *ast, t_token *start, t_token *end);

// check_ast_error.c
void	check_center_error(t_ast *ast, t_token *center);
int		check_redirection_error(t_ast *ast, t_token *node);
int		check_error(t_ast *ast);

// error.c
void	syntax_error_parser(char *string, t_token **list);

// set_node.c
void	set_start_end(t_ast **ast, t_token *start, t_token *end);

// wildcard.c
char	**add_str(char **str, char *add);
int		check_front_center(char *filename, char *pattern, t_mark *mark, int i);
int		check_end(char *filename, char *pattern, t_mark mark, int i);
int		check_wildfixes(char *filename, __uint8_t type, char *pattern);
char	**expand_wildcard(char *arg);

#endif
