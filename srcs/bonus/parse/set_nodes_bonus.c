/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nodes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:37:13 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

// 현재 노드에 start, end 할당.
// 괄호 짝이 맞지 않는 경우는 에러 처리. 예: (ls
// 괄호가 중첩되는 경우는 에러 처리. 예: ((ls))
// 가장 바깥쪽 single pair 괄호는 제거.
void	set_start_end(t_ast **ast, t_token *start, t_token *end)
{
	t_token	*err_token;
	int		single_pair;

	single_pair = check_if_single_pair(start, end);
	*ast = ft_calloc(1, sizeof(t_ast));
	if (*ast)
	{
		err_token = check_bracket(start, end);
		remove_bracket(&start, &end);
		if (err_token)
			(*ast)->error = ft_strdup(err_token->string);
		else if (single_pair && check_if_single_pair(start, end) \
				&& start->type == T_OPEN_BRACKET \
				&& end->type == T_CLOSE_BRACKET)
		{
			(*ast)->error = ft_strdup(start->string);
		}
		(*ast)->start = start;
		(*ast)->end = end;
	}
}
