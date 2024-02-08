/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:31:56 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/08 17:58:08 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	cmd_expand(t_c_expand *expand, t_env_pack *pack)
{
	int		i;
	char	*temp;

	i = -1;
	while (expand->exp_ptrs[++i])
	{
		temp = search_value(expand->exp_ptrs[i], pack);
		if (!temp)
		{
			expand_join(expand, expand->exp_ptrs[i]->exp_name);
			join_remain(expand, ft_strlen(expand->exp_ptrs[i]->exp_name));

			continue ;
		}
		if (expand->exp_ptrs[i]->q_flag == 0)
			expand_add(expand, temp);		// 환경변수 value를 split해보고 split되면 나누어서 붙이기
		else
			expand_join(expand, temp);		// split 없이 바로 strjoin
		join_remain(expand, ft_strlen(expand->exp_ptrs[i]->exp_name));						// 다음 $문자오기 전까지 일반문자열들을 join한다
	}
	ft_printf("\nout: ");
	for (int j = 0; j < split_len(expand->result); j++)
		ft_printf("[%s]\n", expand->result[j]);
}

char	*search_value(t_exp_pair *pair, t_env_pack *pack)
{
	t_env	*target;
	char	*value;
	char	*out;

	ft_printf("SEARCH\n");
	ft_printf("search for: [%s]\n\n", pair->exp_name);
	if (pair->q_flag == '\'')
		return (NULL);
	target = find_env(pair->exp_name, pack);
	if (!target)
		return (ft_strdup(""));
	else
		return (ft_strdup(target->value));
}

void	expand_add(t_c_expand *expand, char *temp)
{
	char	**split;
	char	*out;
	int		i;
	int		split_l;

	ft_printf("ADD\n");
	ft_printf("need to add: [%s]\n\n", temp);
	if (!*temp)
		return (free(temp));
	split = ft_split(temp, ' ');
	i = 0;
	split_l = split_len(split);
	while (expand->result && expand->result[i + 1])
		i++;
	if (!expand->result)
	{
		while (i < split_l)
		{
			expand->result = add_str(expand->result, split[i]);
			i++;
		}
		return ;
	}
	out = ft_strjoin(expand->result[i], split[0]);
	free(expand->result[i]);
	expand->result[i] = out;
	i = 1;
	while (i < split_l)
	{
		expand->result = add_str(expand->result, split[i]);
		i++;
	}
	return (free(split));
}

void	expand_join(t_c_expand *expand, char *temp)
{
	char	*out;
	int		i;

	ft_printf("JOIN\n");
	i = 0;
	while (expand->result && expand->result[i])
		i++;
	ft_printf("i: %d\n", i);
	if (i)
	{
		out = ft_strjoin(expand->result[i - 1], temp);
		ft_printf("target: %s\n", expand->result[i - 1]);
		free(expand->result[i - 1]);						// double free error;
	}
	if (!expand->result)
	{
		expand->result = add_str(expand->result, temp);
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

	ft_printf("REMAIN\n");
	i = 1;
	while (expand->original[i])
	{
		if (expand->original[i] == '$')
			break ;
		i++;
	}
	new = ft_substr(expand->original, len, i - len);
	ft_printf("need to join: [%s]\n\n", new);
	new_orig = ft_substr(expand->original, i, ft_strlen(expand->original) - i);
	ft_printf("new_orig: [%s]\n", new_orig);
	free(expand->original);
	expand->original = new_orig;
	return (expand_join(expand, new));
}
