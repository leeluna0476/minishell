/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:31:56 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/07 14:23:37 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	do_cmd_expand(t_c_expand *expand, t_env_pack *pack)		// 미완성
{
	int		i;
	char	*temp;

	i = 0;
	while (expand->exp_ptrs[i])
	{
		temp = search_expand(expand->exp_ptrs[i], pack);
		i++;
	}
}

char	*search_expand(t_exp_pair *pair, t_env_pack *pack)
{
	char	*exp_name;
	t_env	*node;
	char	*out;

	exp_name = find_env_name(pair->exp_pos);
	if (pair->q_flag == '\'' || exp_name)
		return (0);
	else
	{
		node = find_env(exp_name, pack);
		if (!node)
			return (0);
		else
			return (ft_strdup(node->value));
	}
}
