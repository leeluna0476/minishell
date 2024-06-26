/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 10:40:14 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "execute.h"

void	split_free(char **split)
{
	int	i;
	int	s_len;

	i = -1;
	s_len = split_len(split);
	while (++i < s_len)
		free(split[i]);
	free(split);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

char	**add_str(char **str, char *add)
{
	char	**new;
	int		i;

	if (!add)
		return (str);
	i = 0;
	while (str && str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit(1);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = add;
	i++;
	new[i] = 0;
	if (str)
		free(str);
	return (new);
}

char	**merge_strs(char **orig, char **new_strs)
{
	int		orig_len;
	int		new_len;
	int		idx;
	char	**out;

	if (!orig)
		return (new_strs);
	if (!new_strs)
		return (orig);
	orig_len = split_len(orig);
	new_len = split_len(new_strs);
	out = malloc(sizeof(char *) * (orig_len + new_len + 1));
	if (!out)
		exit(1);
	idx = -1;
	while (++idx < orig_len)
		out[idx] = orig[idx];
	idx = -1;
	while (++idx <= new_len)
		out[idx + orig_len] = new_strs[idx];
	free(orig);
	free(new_strs);
	return (out);
}

void	ft_assert(int expression, const char *arg, int exit_num)
{
	if (expression)
		return ;
	ft_perror(arg, exit_num);
}
