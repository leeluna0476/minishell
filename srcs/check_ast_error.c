/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 12:05:36 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//&& !is_redirection(center->next->type))
void	check_center_error(t_ast *ast, t_token *center)
{
	if ((!(center->next) || !(center->prev)) \
		|| (center->next->type == T_AND || center->next->type == T_OR \
		|| center->next->type == T_PIPE \
		|| center->next->type == T_CLOSE_BRACKET \
		|| center->prev->type == T_AND || center->prev->type == T_OR \
		|| center->prev->type == T_PIPE \
		|| center->prev->type == T_OPEN_BRACKET))
	{
		free(ast->error);
		ast->error = ft_strdup(center->string);
	}
}

int	check_redirection_error(t_ast *ast, t_token *node)
{
	if (!(node->next))
	{
		free(ast->error);
		ast->error = ft_strdup("newline");
		return (1);
	}
	return (0);
}

int	check_error(t_ast *ast)
{
	if (ast->error)
		return (1);
	if (ast->left && ast->left->error)
	{
		ast->error = ft_strdup(ast->left->error);
		return (1);
	}
	if (ast->right && ast->right->error)
	{
		ast->error = ft_strdup(ast->right->error);
		return (1);
	}
	return (0);
}
