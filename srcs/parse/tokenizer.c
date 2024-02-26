/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:24:18 by seojilee          #+#    #+#             */
<<<<<<< HEAD:srcs/parse/tokenizer.c
/*   Updated: 2024/02/16 13:32:49 by seojilee         ###   ########.fr       */
=======
/*   Updated: 2024/02/23 19:46:19 by seojilee         ###   ########.fr       */
>>>>>>> yusekim_test:srcs/tokenizer.c
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

// 메타문자가 아닌 일반 문자로 시작하는 단어.
// 중간부터 따옴표가 오면 함께 묶어준다.
// 닫히지 않는다면 오류.
int	get_word(char *line, char **string, t_type *type)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_meta1(line[i]) \
		&& line[i] != '(' && line[i] != ')')
	{
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

// 토큰을 생성하고 리스트에 추가한다.
void	update_list(t_token **list, char *string, t_type type)
{
	t_token	*node;

	node = new_token(string, type);
	add_token(list, node);
}

// 주어진 문자열을 토큰화한다.
t_token	*tokenizer(char *line)
{
	t_token		*list;
	char		*string;
	int			i;
	t_type		type;

	list = NULL;
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
		update_list(&list, string, type);
		free(string);
		i += remove_space(&(line[i]));
	}
	return (list);
}
