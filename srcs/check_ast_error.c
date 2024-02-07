#include "AST.h"

void	check_center_error(t_ast *ast, t_token *center)
{
	if ((!(center->next) || !(center->prev)) \
		|| ((center->next->type != T_WORD \
		&& center->next->type != T_OPEN_BRACKET \
		&& !is_redirection(center->next->type)) \
		|| (center->prev->type != T_WORD \
		&& center->prev->type != T_CLOSE_BRACKET)))
	{
		free(ast->error);
		ast->error = NULL;
		ast->error = ft_strdup(center->string);
	}
}

int	check_redirection_error(t_ast *ast, t_token *node)
{
	if (!(node->next))
	{
		free(ast->error);
		ast->error = NULL;
		ast->error = ft_strdup("newline");
		return (1);
	}
	return (0);
}

int	check_error(t_ast *ast)
{
	if (ast->error)
		return (1);
	if ((ast->left && ast->left->error))
	{
		ast->error = ft_strdup(ast->left->error);
		return (1);
	}
	if ((ast->right && ast->right->error))
	{
		ast->error = ft_strdup(ast->right->error);
		return (1);
	}
	return (0);
}
