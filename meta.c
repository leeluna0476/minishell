/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:34:40 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/02 10:49:49 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_struct.h"

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

int	is_meta2(char c)
{
	const char	*meta2 = "()\"\'";
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
	return (i);
}
