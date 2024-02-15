/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youwin0802 <youwin0802@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:03:15 by youwin0802        #+#    #+#             */
/*   Updated: 2024/02/15 14:57:52 by youwin0802       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	set_fd(t_cmd *cmd, int *pipe_fds, int *redir_fds)
{
	if (cmd->in_redirs)
	{
		redir_fds[0] = open(cmd->in_redirs->filename[1], O_RDONLY);
		if (redir_fds[0] == -1)
			ft_printf("open error[%s]\n", cmd->in_redirs->filename[1]); // exit status = 1
	}
	else
		redir_fds[0] = pipe_fds[2];
	if (cmd->out_redirs)
	{
		if (cmd->out_redirs->type == T_D_GREATER)
			redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (redir_fds[1] == -1)
			ft_printf("open error [%s]\n", cmd->out_redirs->filename[1]);
	}
	else if (pipe_fds)
		redir_fds[1] = pipe_fds[1];
}

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
