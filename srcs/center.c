/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:59:44 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 10:00:32 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

// 어떤 토큰을 기준으로 가지를 나눌지.
// 괄호를 만나면 짝을 만날 때까지 이동.
// 우선순위: 1. (), 2. &&, ||, 3. |

t_token	*take_bracket(t_token *curr, t_token *start)
{
	int	flag;

	flag = 1;
	while (flag && curr && curr->next != start)
	{
		if (curr->type == T_OPEN_BRACKET)
			flag--;
		else if (curr->type == T_CLOSE_BRACKET)
			flag++;
		curr = curr->prev;
	}
	return (curr);
}

t_token	*get_logical_exp(t_ast *ast, t_token *start, t_token *end)
{
	t_token	*curr;

	curr = end;
	while (curr && curr->next != start)
	{
		if (curr->type == T_CLOSE_BRACKET)
			curr = take_bracket(curr->prev, start);
		if (curr && curr->next != start \
			&& (curr->type == T_AND || curr->type == T_OR))
		{
			check_center_error(ast, curr);
			return (curr);
		}
		if (curr && curr->next != start)
			curr = curr->prev;
	}
	return (NULL);
}

t_token	*get_pipeline(t_ast *ast, t_token *start, t_token *end)
{
	t_token	*curr;

	curr = end;
	while (curr && curr->next != start)
	{
		if (curr->type == T_PIPE)
		{
			check_center_error(ast, curr);
			return (curr);
		}
		curr = curr->prev;
	}
	return (NULL);
}

t_token	*get_center(t_ast *ast, t_token *start, t_token *end)
{
	t_token	*curr;

	curr = get_logical_exp(ast, start, end);
	if (curr)
		return (curr);
	curr = get_pipeline(ast, start, end);
	if (curr)
		return (curr);
	return (NULL);
}
