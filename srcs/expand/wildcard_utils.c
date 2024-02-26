/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:47:48 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/26 11:22:53 by yusekim          ###   ########.fr       */
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
				expand->result = insert_strs(expand->result, temp_wildcard, &i);
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
	int		o_idx;
	int		n_idx;
	int		orig_len;
	int		new_len;
	char	**res;

	orig_len = split_len(orig);
	new_len = split_len(new);
	res = ft_calloc(orig_len + new_len, sizeof(char *));
	if (!res)
		exit (1);
	o_idx = -1;
	while (++o_idx < *i)
		res[o_idx] = orig[o_idx];
	free(orig[o_idx]);
	n_idx = -1;
	while (++n_idx < new_len)
		res[o_idx + n_idx] = new[n_idx];
	while (++o_idx < orig_len)
		res[o_idx + n_idx] = orig[o_idx];
	free(orig);
	free(new);
	*i += new_len;
	return (res);
}
