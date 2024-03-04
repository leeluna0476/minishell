/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:47:48 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 15:28:25 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	check_tilde(t_c_expand *expand, char *ptr)
{
	int	i;

	i = 0;
	while (expand->original && expand->original + i != ptr)
		i++;
	if (i > 0)
		return (0);
	if (ft_strlen(ptr) == 1 && *(ptr + 1) == '/')
		return (1);
	else
		return (0);
}

void	only_wildcard(t_c_expand *expand)
{
	char	**temp_wildcard;

	expand->result = add_str(expand->result, ft_strdup(expand->original));
	if (expand->wild_num && expand->wild_flag == 0)
	{
		temp_wildcard = expand_wildcard(expand->original);
		if (temp_wildcard)
		{
			split_free(expand->result);
			expand->result = temp_wildcard;
		}
	}
	return ;
}

void	do_wildcard(t_c_expand *expand, int i, int bound)
{
	char		**temp_wildcard;

	while (expand->result && expand->result[i] && bound--)
	{
		if (scan_for_wildcard(expand->result[i]))
		{
			temp_wildcard = expand_wildcard(expand->result[i]);
			if (temp_wildcard)
			{
				expand->result = insert_strs(expand->result, temp_wildcard, &i);
				split_free(temp_wildcard);
				temp_wildcard = NULL;
				continue ;
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
	result[orig_len + new_len - 1] = NULL;
	idx = -1;
	while (++idx < *i)
		result[idx] = ft_strdup(orig[idx]);
	while (*new != NULL)
		result[idx++] = ft_strdup(*new++);
	jdx = 0;
	while (idx - new_len < orig_len)
		result[idx++] = ft_strdup(orig[*i + ++jdx]);
	split_free(orig);
	*i = *i + new_len;
	return (result);
}
