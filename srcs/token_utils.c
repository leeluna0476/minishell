/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:25:20 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 08:53:39 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

// 새로운 토큰 생성.
t_token	*new_token(char *string, t_type type)
{
	t_token	*token;

	if (string)
	{
		token = ft_calloc(1, sizeof(t_token));
		if (token)
		{
			token->string = ft_strdup(string);
			token->type = type;
		}
		return (token);
	}
	return (NULL);
}

// list의 마지막 토큰 구하기. (NULL 바로 전)
t_token	*last_token(t_token *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

// list에 토큰 붙이기.
void	add_token(t_token **list, t_token *token)
{
	t_token	*last;

	if (list)
	{
		if (*list)
		{
			last = last_token(*list);
			last->next = token;
			token->prev = last;
		}
		else
		{
			*list = token;
		}
	}
}

// 토큰 메모리 해제 && 댕글링 포인터 방지.
void	free_token(t_token **token)
{
	free((*token)->string);
	free((*token));
	*token = NULL;
}

// 토큰 리스트 메모리 해제 && 댕글링 포인터 방지.
void	free_tokens(t_token **tokens)
{
	t_token	*head;
	t_token	*temp;

	head = *tokens;
	while (head)
	{
		temp = head->next;
		free_token(&head);
		head = temp;
	}
	*tokens = NULL;
}
