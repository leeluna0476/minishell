/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:59:44 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:37:03 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

// 어떤 토큰을 기준으로 가지를 나눌지.
// 괄호를 만나면 짝을 만날 때까지 이동.
// 우선순위: 1. (), 2. &&, ||, 3. |

// 괄호를 기준으로 토큰 건너뛰기.
// (ls && ls) | ls -> (ls && ls) 건너뛰기.
// logical_exp 못 찾았으니 파이프라인 체크로 넘어감.
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

// 논리연산자 토큰이 존재하는지 검사하기. 있다면 해당 토큰 반환.
// 괄호 속 내용은 건너뛰기.
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

// 파이프 토큰이 존재하는지 검사하기. 있다면 해당 토큰 반환.
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

// logical_exp 또는 pipeline인지 검사.
// 논리연산자 토큰을 먼저 반환. 없다면 파이프 토큰 반환.
// 괄호는 건너뛴다.
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
