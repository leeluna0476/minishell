/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:03:15 by youwin0802        #+#    #+#             */
/*   Updated: 2024/02/19 13:11:30 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

	if (stat(str, &path_stat) != 0)
		ft_perror(str, 128);
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

void	exec_parent(t_info *info)
{
	if (info->redir_fds[0] > 2)
		close(info->redir_fds[0]);
	if (info->redir_fds[1] > 2)
		close(info->redir_fds[1]);
	if (info->fork_num != 0 && info->pipe_fds[2])
		close(info->pipe_fds[2]);
	if (info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
	info->pipe_fds[2] = info->pipe_fds[0];
}
