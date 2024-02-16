/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:57:56 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 10:58:21 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

// 괄호 짝 확인.
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
			if (!flag && !(*last))
				*last = curr;
		}
		curr = curr->next;
	}
	*start = curr;
	return (flag);
}

// 주소 크기 비교. 재차 확인.
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
	if (first && first->prev && first->prev >= start \
		&& first->prev->type != T_AND && first->prev->type != T_OR \
		&& first->prev->type != T_PIPE)
		return (first->prev);
	else if (last && last->next && last->next <= end \
		&& last->next->type != T_AND && last->next->type != T_OR \
		&& last->next->type != T_PIPE)
		return (last->next);
	return (NULL);
}

// 지워도 되는 괄호 유무 판단.
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

// 지워도 되는 괄호가 있다면 지운다. (건너뛴다)
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
