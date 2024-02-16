/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:36:46 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 12:03:40 by seojilee         ###   ########.fr       */
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

// a 반환.
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
