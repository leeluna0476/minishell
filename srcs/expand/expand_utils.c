/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:57:36 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 09:41:08 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	build_exp_pair(t_c_expand *expand, char *ptr, int q_flag)
{
	t_exp_pair	*new;

	new = ft_calloc(1, sizeof(t_exp_pair));
	if (!new)
		exit (1);
	new->q_flag = q_flag;
	new->exp_name = find_env_name(ptr);
	if (!expand->exp_num)
	{
		expand->exp_ptrs = malloc(sizeof(t_c_expand *) * 2);
		if (!expand->exp_ptrs)
			exit(1);
		expand->exp_num++;
		expand->exp_ptrs[expand->exp_num] = 0;
		expand->exp_ptrs[0] = new;
		return ;
	}
	else
		append_exp_ptr(expand, new);
}

void	append_exp_ptr(t_c_expand *expand, t_exp_pair *newpair)
{
	t_exp_pair	**res;
	int			i;

	expand->exp_num++;
	res = malloc(sizeof(t_c_expand *) * (expand->exp_num + 1));
	if (!res)
		exit(1);
	res[expand->exp_num] = 0;
	i = 0;
	while (expand->exp_ptrs && expand->exp_ptrs[i])
	{
		res[i] = expand->exp_ptrs[i];
		i++;
	}
	res[i] = newpair;
	free(expand->exp_ptrs);
	expand->exp_ptrs = res;
}

char	*find_env_name(char *ptr)
{
	int		i;

	if (*ptr == '*')
		return (ft_strdup("*"));
	i = 1;
	if (ft_isdigit(ptr[i]) || ptr[i] == '?')
		return (ft_substr(ptr, 0, i + 1));
	while (ptr[i])
	{
		if (!(ft_isalnum(ptr[i]) || ptr[i] == '_'))
			break ;
		i++;
	}
	return (ft_substr(ptr, 0, i));
}

char	*appand_string(char *result, char *original, int *start, int end)
{
	char	*out;
	char	*temp;

	out = 0;
	if (!*start)
	{
		out = ft_substr(original, *start, end);
		*start = end + 1;
		return (out);
	}
	else
	{
		temp = ft_substr(original, *start, end - *start);
		out = ft_strjoin(result, temp);
		free(result);
		free(temp);
		*start = end + 1;
		return (out);
	}
}

void	add_split(t_c_expand *expand, char **split, int split_len, int idx)
{
	char	*new;

	new = ft_strjoin(expand->result[idx], split[0]);
	free(split[0]);
	free(expand->result[idx]);
	expand->result[idx] = new;
	idx = 1;
	while (idx < split_len)
	{
		expand->result = add_str(expand->result, split[idx]);
		idx++;
	}
	free(split);
}
