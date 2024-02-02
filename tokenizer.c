/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:24:18 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/02 12:55:57 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

int	is_space(char c)

{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

t_type	get_type(char *string, int i)
{
	t_type	type;

	type = T_WORD;
	if (is_meta1(string[0]))
		set_type_meta1(string[0], i, &type);
	else if (is_meta2(string[0]))
	{
		if (string[0] == '(')
			type = T_OPEN_BRACKET;
		else if (string[0] == ')')
			type = T_CLOSE_BRACKET;
	}
	return (type);
}

int	remove_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

int	get_word(char *line, char **string, t_type *type)
{
	int	i;

	i = 0;
	while (line[i] && !is_space(line[i]) \
		&& !is_meta1(line[i]) && !is_meta2(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	return (i);
}

void	syntax_error(char *string, t_token **list)
{
	// print error
	printf("syntax error: `%s`\n", string);
	free(string);
	free_tokens(list);
}

t_token	*tokenizer(char *line)
{
	t_token		*list;
	t_token		*node;
	char		*string;
	int			i;
	t_type		type;

	list = NULL;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_meta1(line[i]))
			i += get_meta1(&(line[i]), &string, &type);
		else if (is_meta2(line[i]))
			i += get_meta2(&(line[i]), &string, &type);
		else
			i += get_word(&(line[i]), &string, &type);
		if (type == T_ERROR)
		{
			syntax_error(string, &list);
			break ;
		}
		node = new_token(string, type);
		add_token(&list, node);
		free(string);
		i += remove_space(&(line[i]));
	}
	return (list);
}

void	leaks(void)
{
	system("leaks -q a.out");
}

int	main(void)
{
	t_token	*tokens;
	t_token	*curr;

	atexit(leaks);
	tokens = tokenizer("<<<<<<<<<<<<<<<eof ls -l | wc -l >> out");
	curr = tokens;
	while (curr)
	{
		printf("%s  ", curr->string);
		printf("%d\n", curr->type);
		curr = curr->next;
	}
	free_tokens(&tokens);
}
