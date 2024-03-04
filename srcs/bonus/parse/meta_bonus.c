/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:34:40 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:37:11 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_bonus.h"

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

// meta2: meta1이 아닌 메타문자.
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
