/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ast_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/26 18:30:00 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// center 앞뒤로 오면 안 되는 type이 존재한다면 에러 반환.
// ls && || -> error
// ls | && -> error
// ls && (ls) -> error
void	check_center_error(t_ast *ast, t_token *center)
{
	if (!(center->prev))
		set_parse_error(ast, center->string);
	else if (!(center->next))
		set_parse_error(ast, "newline");
	else if (center->prev->type == T_AND || center->prev->type == T_OR \
		|| center->prev->type == T_PIPE \
		|| center->prev->type == T_OPEN_BRACKET)
		set_parse_error(ast, center->prev->string);
	else if (center->next->type == T_AND || center->next->type == T_OR \
		|| center->next->type == T_PIPE \
		|| center->next->type == T_CLOSE_BRACKET)
		set_parse_error(ast, center->next->string);
//
//
//	if ((!(center->next) || !(center->prev)) \
//		|| (center->next->type == T_AND || center->next->type == T_OR \
//		|| center->next->type == T_PIPE \
//		|| center->next->type == T_CLOSE_BRACKET \
//		|| center->prev->type == T_AND || center->prev->type == T_OR \
//		|| center->prev->type == T_PIPE \
//		|| center->prev->type == T_OPEN_BRACKET))
//	{
//		set_parse_error(ast, center->string);
//	}
}

// 리다이렉션 뒤에 아무것도 없거나 T_WORD 외의 타입이 온다면 에러 설정.
void	check_redirection_error(t_ast *ast)
{
	t_token	*curr;

	curr = ast->start;
	while (curr && curr->prev != ast->end && !(ast->error))
	{
		if (is_redirection(curr->type))
		{
			if (!(curr->next))
				set_parse_error(ast, "newline");
			else if (curr->next->type != T_WORD)
				set_parse_error(ast, curr->next->string);
		}
		curr = curr->next;
	}
}

// 트리에 에러가 발생했는지 확인.
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
