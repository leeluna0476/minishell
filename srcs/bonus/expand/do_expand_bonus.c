/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_expand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:31:56 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:36:41 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_bonus.h"

void	do_expand(t_c_expand *exp, t_env_pack *pack)
{
	int		i;
	char	*temp;

	i = -1;
	if (exp->exp_num == 0)
		return (only_wildcard(exp));
	while (exp->exp_ptrs[++i])
	{
		temp = search_value(exp->exp_ptrs[i], pack);
		if (!temp)
		{
			expand_join(exp, ft_strdup(exp->exp_ptrs[i]->exp_name));
			join_remain(exp, ft_strlen(exp->exp_ptrs[i]->exp_name));
			continue ;
		}
		if (exp->exp_ptrs[i]->q_flag == 0)
			expand_add(exp, temp);
		else
			expand_join(exp, temp);
		join_remain(exp, ft_strlen(exp->exp_ptrs[i]->exp_name));
	}
	do_wildcard(exp, split_len(exp->result) - 1, split_len(exp->result));
}

char	*search_value(t_exp_pair *pair, t_env_pack *pack)
{
	t_env	*target;

	if (pair->q_flag == '\'' || !*pair->exp_name)
		return (NULL);
	if (*pair->exp_name == '*')
		return (ft_strdup("*"));
	target = find_env(pair->exp_name, pack);
	if (!target)
	{
		if (ft_strlen(pair->exp_name) == 1)
			return (ft_strdup("$"));
		else
			return (ft_strdup(""));
	}
	else
		return (ft_strdup(target->value));
}

void	expand_join(t_c_expand *expand, char *temp)
{
	char	*out;
	int		i;

	i = 0;
	while (expand->result && expand->result[i])
		i++;
	if (i)
	{
		out = ft_strjoin(expand->result[i - 1], temp);
		free(expand->result[i - 1]);
	}
	if (!expand->result)
	{
		expand->result = add_str(expand->result, ft_strdup(temp));
	}
	else
		expand->result[i - 1] = out;
	return (free(temp));
}

void	join_remain(t_c_expand *expand, int len)
{
	int		i;
	char	*new;
	char	*new_orig;

	i = 1;
	while (expand->original[i])
	{
		if (expand->original[i] == '$' || expand->original[i] == '~')
			break ;
		i++;
	}
	new_orig = ft_substr(expand->original, i, ft_strlen(expand->original) - i);
	new = ft_substr(expand->original, len, i - len);
	free(expand->original);
	expand->original = new_orig;
	if (new)
	{
		return (expand_join(expand, new));
	}
	else
		return ;
}

void	expand_add(t_c_expand *expand, char *temp)
{
	char	**split;
	char	*out;
	int		i;
	int		split_l;

	if (!*temp)
		return (free(temp));
	split = ft_split(temp, ' ');
	split_l = split_len(split);
	i = 0;
	while (expand->result && expand->result[i + 1])
		i++;
	if (!expand->result)
		expand->result = split;
	else if (split_l == 1)
	{
		out = ft_strjoin(expand->result[i], temp);
		free(expand->result[i]);
		expand->result[i] = out;
		split_free(split);
	}
	else
		add_split(expand, split, split_l, i);
	do_wildcard(expand, i, split_l - 1);
	return (free(temp));
}
