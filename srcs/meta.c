/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:34:40 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/07 20:48:20 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

// meta1: 최대 2개까지 하나의 토큰이 될 수 있는 메타문자.
// meta1인지 판별.
int	is_meta1(char c)
{
	const char	*meta1 = "><&|;";
	int			i;

	i = 0;
	while (meta1[i])
	{
		if (c == meta1[i])
			return (1);
		i++;
	}
	return (0);
}

// meta2: 짝이 있어야 하는 메타문자.
// meta2인지 판별.
int	is_meta2(char c)
{
	const char	*meta2 = "\n()\"\'";
	int			i;

	i = 0;
	while (meta2[i])
	{
		if (c == meta2[i])
			return (1);
		i++;
	}
	return (0);
}

// meta1에 속하는 문자에 타입 부여.
void	set_type_meta1(char c, int i, t_type *type)
{
	if (c == '<')
	{
		*type = T_LESSER;
		if (i == 2)
			*type = T_D_LESSER;
	}
	else if (c == '>')
	{
		*type = T_GREATER;
		if (i == 2)
			*type = T_D_GREATER;
	}
	else if (c == '&')
	{
		if (i == 2)
			*type = T_AND;
	}
	else if (c == '|')
	{
		*type = T_PIPE;
		if (i == 2)
			*type = T_OR;
	}
}

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

// meta2에 속하는 토큰 가져오기.
int	get_meta2(char *line, char **string, t_type *type)
{
	int	i;

	i = 1;
	if (line[0] == '\"' || line[0] == '\'')
	{
		while (line[i] && line[i] != line[0])
			i++;
		i++;
	}
	*string = ft_substr(line, 0, i);
	*type = get_type(*string, i);
	if ((*string)[0] != (*string)[i - 1])
		*type = T_ERROR;
	return (i);
}
