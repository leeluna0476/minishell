/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:57:56 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/01 10:28:49 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	return (flag);
}

int	tokcmp(t_token *token1, t_token *token2)
{
	t_token	*curr;

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
		if (tokcmp(first->prev, start) == 1 \
			&& first->prev->type != T_AND && first->prev->type != T_OR)
			return (first->prev);
	}
	else if (last && last->next)
	{
		if (tokcmp(last->next, end) == -1 \
			&& last->next->type != T_AND && last->next->type != T_OR)
			return (last->next);
	}
	return (NULL);
}

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
