/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:36:46 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 13:26:32 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

// meta1에 속하는 토큰 가져오기.
int	get_meta1(char *line, char **string, t_type *type)
{
	int		i;

	i = 0;
	while (line[i] && line[0] == line[i] && i < 2 && !is_space(line[i]))
		i++;
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	return (i);
}

// 문자열이 따옴표로 묶여있다면, 짝이 맞는지 flag를 지정하고 범위를 반환.
// a: 마지막으로 짝을 검사한 따옴표의 인덱스.
	// line = "a"b'c'
	// line[a] = '

	// line = "ab'c'
	// line[a] = "
int	get_quote(char *line, int *flag, int *idx)
{
	int	a;
	int	f;
	int	i;

	a = 0;
	f = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ' ' || line[i] == '(' || line[i] == ')') && !f)
			break ;
		if (line[i] == '\"' || line[i] == '\'')
		{
			f++;
			a = i++;
			while (line[i] && f)
				if (line[i++] == line[a])
					f--;
			i--;
		}
		i++;
	}
	*flag = f;
	*idx = i;
	return (a);
}

// meta2에 속하는 토큰 가져오기.
// 괄호는 get_quote를 호출하지 않고 i = 1을 그대로 가져간다. 괄호 한 짝 == 토큰.
// 따옴표가 존재하면 get_quote를 호출하여 오류를 검사하고 토큰 범위를 가져온다.
int	get_meta2(char *line, char **string, t_type *type)
{
	int	i;
	int	a;
	int	flag;

	flag = 0;
	i = 1;
	if (line[0] == '\"' || line[0] == '\'')
		a = get_quote(line, &flag, &i);
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	if (flag % 2 != 0)
	{
		*type = T_ERROR;
		free(*string);
		*string = ft_substr(line, a, 1);
	}
	return (i);
}
