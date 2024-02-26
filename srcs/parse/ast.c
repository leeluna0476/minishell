/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/26 18:27:58 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 가지 분할의 기준점이 되는 논리 연산자 또는 파이프를 확인.
// 기준점이 없다면 simple command.
void	generate_ast(t_ast **ast, t_token *start, t_token *end)
{
	t_token	*center;

	center = get_center(*ast, start, end);
	if (check_error(*ast))
		return ;
	if (center)
	{
		(*ast)->type = center->type;
		set_start_end(&((*ast)->left), start, center->prev);
		generate_ast(&((*ast)->left), (*ast)->left->start, (*ast)->left->end);
		if (check_error(*ast))
		{
			return ;
		}
		set_start_end(&((*ast)->right), center->next, end);
		generate_ast(&((*ast)->right), \
			(*ast)->right->start, (*ast)->right->end);
		if (check_error(*ast))
			return ;
	}
	else
	{
		(*ast)->type = T_WORD;
		check_redirection_error(*ast);
		check_error(*ast);
	}
}
