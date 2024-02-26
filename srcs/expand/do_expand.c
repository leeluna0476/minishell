/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:31:56 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/26 14:45:44 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	do_expand(t_c_expand *expand, t_env_pack *pack)
{
	int		i;
	char	*temp;

	i = -1;
	if (expand->exp_num == 0)
	{
		expand->result = add_str(expand->result, ft_strdup(expand->original));
		if (expand->wild_num && expand->wild_flag == 0)
			expand->result = expand_wildcard(expand->original);
		return ;
	}
	while (expand->exp_ptrs[++i])
	{
		temp = search_value(expand->exp_ptrs[i], pack);
		if (!temp)
		{
			expand_join(expand, ft_strdup(expand->exp_ptrs[i]->exp_name));
			join_remain(expand, ft_strlen(expand->exp_ptrs[i]->exp_name));
			continue ;
		}
		if (expand->exp_ptrs[i]->q_flag == 0)
			expand_add(expand, temp);		// 환경변수 value를 split해보고 split되면 나누어서 붙이기
		else
			expand_join(expand, temp);		// split 없이 바로 strjoin
		join_remain(expand, ft_strlen(expand->exp_ptrs[i]->exp_name));						// 다음 $문자오기 전까지 일반문자열들을 join한다
	}
	do_wildcard(expand, split_len(expand->result) - 1);
}

char	*search_value(t_exp_pair *pair, t_env_pack *pack)
{
	t_env	*target;

	if (pair->q_flag == '\'')
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
		if (expand->original[i] == '$')
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
	i = 1;
	while (expand->result && expand->result[i])
		i++;
	i -= 1;
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
	do_wildcard(expand, i);
	return (free(temp));
}
