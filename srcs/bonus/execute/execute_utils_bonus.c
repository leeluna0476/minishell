/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:03:15 by youwin0802        #+#    #+#             */
/*   Updated: 2024/03/04 18:36:14 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"
#include "env_bonus.h"

char	**make_envp(t_env_pack *envs)
{
	t_env	*cur;
	char	*temp_str;
	char	*envp_str;
	char	**result;

	result = 0;
	cur = envs->origin_head;
	while (cur)
	{
		temp_str = ft_strjoin(cur->name, "=");
		envp_str = ft_strjoin(temp_str, cur->value);
		free(temp_str);
		result = add_str(result, envp_str);
		cur = cur->origin_next;
	}
	return (result);
}

int	is_route(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str)
{
	struct stat	path_stat;

	stat(str, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else
		return (0);
}

char	*path_join(char *path, char *arg)
{
	char	*temp;
	char	*out;

	temp = ft_strjoin(path, "/");
	out = ft_strjoin(temp, arg);
	free(temp);
	return (out);
}

int	get_exitstat(t_env_pack *pack)
{
	t_env	*target_node;

	target_node = find_env("?", pack);
	return (ft_atoi(target_node->value));
}
