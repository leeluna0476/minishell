/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:31:56 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/10 21:01:37 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	cmd_expand(t_c_expand *expand, t_env_pack *pack)
{
	int		i;
	char	*temp;

	i = -1;
	if (expand->exp_num == 0)
	{
		expand->result = add_str(expand->result, ft_strdup(expand->original));
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
}

char	*search_value(t_exp_pair *pair, t_env_pack *pack)
{
	t_env	*target;
	char	*value;
	char	*out;

	if (pair->q_flag == '\'')
		return (NULL);
	target = find_env(pair->exp_name, pack);
	if (!target)
		return (ft_strdup(""));
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
	int		count;
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
	i = 0;
	while (expand->result[i])
		i++;
	if (split_l == 1)
	{
		if (!expand->result)
			expand->result = add_str(expand->result, temp);
		else
		{
			out = ft_strjoin(expand->result[i - 1], temp);
			free(expand->result[i - 1]);
			expand->result[i - 1] = out;
			free(temp);
		}
		return (split_free(split));
	}
	if (!expand->result)
		expand->result = split;
	else
	{
		out = ft_strjoin(expand->result[i - 1], split[0]);
		free(split[0]);
		free(expand->result[i - 1]);
		expand->result[i - 1] = out;
		i = 0;
		while (++i < split_l)
			expand->result = add_str(expand->result, split[i]);
		free(split);
	}
	return (free(temp));
}
