/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:32:31 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 15:21:56 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	**expand(char *data, t_env_pack *package, int flag)
{
	t_c_expand	env_info;

	ft_memset(&env_info, 0, sizeof(t_c_expand));
	scan_n_setup(&env_info, data);
	if (flag)
		env_info.result = add_str(env_info.result, ft_strdup(data));
	delete_quotes(&env_info);
	find_position(&env_info);
	if (env_info.exp_num && flag && split_len(env_info.result) == 1)
		env_info.result = add_str(env_info.result, ft_strdup(""));
	do_expand(&env_info, package);
	free_expand(&env_info);
	return (env_info.result);
}

void	scan_n_setup(t_c_expand *expand, char *data)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	expand->original = data;
	while (data[i])
	{
		if (q_flag == 0 && (data[i] == '\'' || data[i] == '"'))
			q_flag = data[i];
		else if (q_flag == data[i])
			q_flag = 0;
		if (data[i] == '$' || data[i] == '~')
			build_exp_pair(expand, data + i, q_flag);
		else if (data[i] == '*')
		{
			expand->wild_num++;
			expand->wild_flag = q_flag;
		}
		i++;
	}
}

void	delete_quotes(t_c_expand *exp)
{
	char	*result;
	int		i;
	int		flag;
	int		start_pos;

	result = 0;
	i = -1;
	flag = 0;
	start_pos = 0;
	while (exp->original[++i])
	{
		if (!flag && (exp->original[i] == '\'' || exp->original[i] == '"'))
		{
			result = appand_string(result, exp->original, &start_pos, i);
			flag = exp->original[i];
		}
		else if (flag && flag == exp->original[i])
		{
			result = appand_string(result, exp->original, &start_pos, i);
			flag = 0;
		}
	}
	result = appand_string(result, exp->original, &start_pos, i);
	free(exp->original);
	exp->original = result;
}

void	find_position(t_c_expand *expand)
{
	int		i;
	int		j;
	char	*new_o;

	i = -1;
	j = -1;
	if (expand->exp_num == 0)
		return ;
	while (expand->original[++i])
	{
		if (expand->original[i] == '$' || expand->original[i] == '~')
			expand->exp_ptrs[++j]->exp_pos = expand->original + i;
	}
	i = 0;
	while (expand->original[i] && \
	!(expand->original[i] == '$' || expand->original[i] == '~'))
		i++;
	expand->result = add_str(expand->result, ft_substr(expand->original, 0, i));
	if (i)
	{
		new_o = ft_substr(expand->original, i, ft_strlen(expand->original) - i);
		free(expand->original);
		expand->original = new_o;
	}
}

void	free_expand(t_c_expand *expand)
{
	int	i;

	free(expand->original);
	if (!expand->exp_num)
		return ;
	i = 0;
	while (expand->exp_ptrs && expand->exp_ptrs[i])
	{
		free(expand->exp_ptrs[i]->exp_name);
		free(expand->exp_ptrs[i]);
		i++;
	}
	free(expand->exp_ptrs);
}
