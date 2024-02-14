/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:24:18 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:09 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

int	is_space(char c)

{
	if (c != '\n' && (c == ' ' || (c >= '\t' && c <= '\r')))
		return (1);
	return (0);
}

// 토큰의 타입 가져오기.
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
		else if (string[0] == '\n')
			type = T_NEWLINE;
	}
	return (type);
}

// 공백 건너뛰기.
int	remove_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	return (i);
}

// 메타문자가 아닌 일반 단어.
// = 할당연산자의 경우 앞이나 뒤에 공백이 있으면 오류로 처리.
// 예쁜 코드 실패.
int	get_word(char *line, char **string, t_type *type)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] && !is_space(line[i]) \
		&& !is_meta1(line[i]) && line[i] != '(' && line[i] != ')')
	{
		if (line[i] == '=')
			i++;
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
			{
				*string = ft_strdup(&quote);
				*type = T_ERROR;
				return (i);
			}
		}
		i++;
	}
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	return (i);
}

void	syntax_error_tokenizer(char *string, t_token **list)
{
	// print error
	printf("syntax error near unexpected token: `%s`\n", string);
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
	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (is_meta1(line[i]))
				i += get_meta1(&(line[i]), &string, &type);
			else if (is_meta2(line[i]))
				i += get_meta2(&(line[i]), &string, &type);
			else
				i += get_word(&(line[i]), &string, &type);
			if (type == T_ERROR)
			{
				syntax_error_tokenizer(string, &list);
				break ;
			}
			node = new_token(string, type);
			add_token(&list, node);
			free(string);
			i += remove_space(&(line[i]));
		}
	}
	return (list);
}
