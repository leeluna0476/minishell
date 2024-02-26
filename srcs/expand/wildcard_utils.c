/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:47:48 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/26 14:49:19 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	do_wildcard(t_c_expand *expand, int i)
{
	char		**temp_wildcard;

	while (expand->result[i])
	{
		if (scan_for_wildcard(expand->result[i]))
		{
			temp_wildcard = expand_wildcard(expand->result[i]);
			if (temp_wildcard)
			{
				expand->result = insert_strs(expand->result, temp_wildcard, &i);
				split_free(temp_wildcard);
				temp_wildcard = NULL;
			}
		}
		i++;
	}
}

int	scan_for_wildcard(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

char	**insert_strs(char **orig, char **new, int *i)
{
	char	**result;
	int		orig_len;
	int		new_len;
	int		idx;
	int		jdx;

	orig_len = split_len(orig);
	new_len = split_len(new);
	result = malloc(sizeof(char *) * (orig_len + new_len));
	result[orig_len + new_len -1] = NULL;
	idx = -1;
	while (++idx < *i)
		result[idx] = ft_strdup(orig[idx]);
	while (*new != NULL)
		result[idx++] = ft_strdup(*new++);
	jdx = 0;
	while (idx < orig_len)
		result[idx++] = ft_strdup(orig[*i + ++jdx]);
	split_free(orig);
	*i = *i + new_len - 1;
	return (result);
}
