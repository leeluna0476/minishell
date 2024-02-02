/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:25:20 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/02 11:05:28 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

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

t_token	*last_token(t_token *list)
{
	t_token	*curr;

	if (list)
	{
		curr = list;
		while (curr->next != NULL)
			curr = curr->next;
		return (curr);
	}
	return (NULL);
}

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

void	free_token(t_token *token)
{
	free(token->string);
	free(token);
	token = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	**head;
	t_token	*curr;

	head = tokens;
	while (*tokens)
	{
		curr = *tokens;
		*tokens = (*tokens)->next;
		free_token(curr);
	}
	*head = NULL;
}