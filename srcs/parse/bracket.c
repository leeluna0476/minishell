/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:57:56 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/27 11:39:47 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 괄호 짝 확인 및 괄호 내용 유무 확인.
// flag는 T_OPEN_BRACKET을 만나면 증가, T_CLOSE_BRACKET을 만나면 감소.
// flag가 0이면 짝이 맞는다는 뜻. (또는 괄호가 없다는 뜻.)
// T_OPEN_BRACKET 바로 다음 토큰이 T_CLOSE_BRACKET이면 오류.
int	get_bracket_flag(t_token **start, t_token **end, \
					t_token **first, t_token **last)
{
	int		flag;
	t_token	*curr;

	flag = 0;
	curr = *start;
	while (curr && curr->prev != *end)
	{
		if (curr->type == T_OPEN_BRACKET)
		{
			flag++;
			if (!(*first))
				*first = curr;
		}
		else if (curr->type == T_CLOSE_BRACKET)
		{
			flag--;
			if ((!flag || flag < 0) && !(*last))
				*last = curr;
}
		curr = curr->next;
	}
	if (*first && *last && (*first)->next == (*end))
		flag = -1;
	//*start = curr;
	return (flag);
}

//  0: equal
// -1: smaller
//  1: greater
static int	token_cmp(t_token *token1, t_token *token2)
{
	t_token *curr;

	if (token1 == token2)
		return (0);
	curr = token1;
	while (curr)
	{
		if (curr == token2)
			return (-1);
		curr = curr->next;
	}
	return (1);
}

// (주소 크기 비교. 재차 확인.)
// flag를 받아서 괄호 짝이 맞는지 확인. 맞지 않는다면 문제 토큰을 반환.
// first, last: 가장 바깥쪽 괄호.
// 바깥 괄호 앞뒤로 허용되지 않는 type이 오는지 확인. 그렇다면 문제 토큰을 반환.
t_token	*check_bracket(t_token *start, t_token *end)
{
	int		flag;
	t_token	*first;
	t_token	*last;

	first = NULL;
	last = NULL;
	flag = get_bracket_flag(&start, &end, &first, &last);
	if (flag > 0)
		return (first);
	else if (flag < 0)
		return (last);
	if (first && first->prev)
	{
		if (token_cmp(first->prev, start) == 1 \
			&& first->prev->type != T_AND && first->prev->type != T_OR)
			return (first->prev);
	}
	else if (last && last->next)
	{
		if (token_cmp(last->next, end) == -1 \
			&& last->next->type != T_AND && last->next->type != T_OR)
			return (last->next);
	}
	return (NULL);
}

// 지워도 되는 괄호 유무 판단.
// 첫번째 괄호 start에서 닫히는 괄호까지 도달했을 때 그것이 end라면 지운다.
// ex: (ls || (ls && cat file))
	// -> ls || (ls && cat file)
int	check_if_single_pair(t_token *start, t_token *end)
{
	t_token	*curr;
	int		flag;

	curr = start;
	flag = 0;
	while (curr && curr->prev != end)
	{
		if (curr->type == T_OPEN_BRACKET)
			flag++;
		else if (curr->type == T_CLOSE_BRACKET)
			flag--;
		if (curr->type == T_CLOSE_BRACKET && !flag)
			break ;
		curr = curr->next;
	}
	if (curr == end)
		return (1);
	return (0);
}

// 지워도 되는 가장 바깥쪽 괄호(single pair)가 있다면 지운다. (건너뛴다)
void	remove_bracket(t_token **start, t_token **end)
{
	if ((*start)->type == T_OPEN_BRACKET && (*end)->type == T_CLOSE_BRACKET)
	{
		if (check_if_single_pair(*start, *end))
		{
			*start = (*start)->next;
			*end = (*end)->prev;
		}
	}
}

// 괄호 안에 파이프가 있는지 확인.
// 있다면 오류임.
t_token	*check_pipe_in_bracket(t_token *start, t_token *end)
{
	t_token	*curr;
	int		flag;

	if (start->type == T_OPEN_BRACKET && end->type == T_CLOSE_BRACKET)
	{
		flag = 0;
		curr = start;
		while (curr && curr->prev != end)
		{
			if (curr->type == T_OPEN_BRACKET)
				flag++;
			else if (curr->type == T_CLOSE_BRACKET)
				flag--;
			else if (flag && curr->type == T_PIPE)
				return (curr);
			curr = curr->next;
		}
	}
	return (NULL);
}
