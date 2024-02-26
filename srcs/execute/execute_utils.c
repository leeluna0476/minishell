/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:03:15 by youwin0802        #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/22 10:55:54 by yusekim          ###   ########.fr       */
=======
/*   Updated: 2024/02/26 14:43:14 by seojilee         ###   ########.fr       */
>>>>>>> yusekim_test
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
<<<<<<< HEAD
=======
#include "env.h"
>>>>>>> yusekim_test

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
<<<<<<< HEAD
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
=======
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
>>>>>>> yusekim_test
}

void	exec_parent(t_info *info)
{
	if (info->redir_fds[0] > 2)
		close(info->redir_fds[0]);
	if (info->redir_fds[1] > 2)
		close(info->redir_fds[1]);
	if (info->fork_num != 0 && info->prev_fd)
		close(info->prev_fd);
	if (info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
	info->prev_fd = info->pipe_fds[0];
}
