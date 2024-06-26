/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:07:31 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 10:49:32 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "env.h"
#include "signal_handler.h"

void	set_fds(t_cmd *cmd, t_info *info)
{
	info->redir_fds[0] = 0;
	info->redir_fds[1] = 1;
	if (cmd->in_redirs)
		info->redir_fds[0] = open(cmd->in_redirs->filename[1], O_RDONLY);
	else
		info->redir_fds[0] = info->prev_fd;
	if (cmd->out_redirs)
	{
		if (cmd->out_redirs->type == T_D_GREATER)
			info->redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			info->redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
		info->redir_fds[1] = info->pipe_fds[1];
}

void	ft_dup2(t_info *info)
{
	if (info->redir_fds[0] != 0)
	{
		dup2(info->redir_fds[0], STDIN_FILENO);
		close(info->redir_fds[0]);
	}
	if (info->redir_fds[1] != 1)
	{
		dup2(info->redir_fds[1], STDOUT_FILENO);
		close(info->redir_fds[1]);
	}
	if (info->pipe_fds[0])
		close(info->pipe_fds[0]);
	if (info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
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

void	ft_wait(t_info *info, t_env_pack *pack)
{
	char	*exit_code;

	get_waitstatus(info);
	signal_dfl();
	info->fork_num = 0;
	info->last_pid = 0;
	if (info->prev_fd)
		close(info->prev_fd);
	exit_code = ft_itoa(info->exit_status);
	add_env_node(pack, "?", exit_code);
	free(exit_code);
	return ;
}

void	get_waitstatus(t_info *info)
{
	int		status;

	while (info->fork_num--)
	{
		if (waitpid(-1, &status, 0) == info->last_pid)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit: 3", STDOUT_FILENO);
				ft_putchar_fd('\n', STDOUT_FILENO);
				info->exit_status = WTERMSIG(status) + 128;
			}
			else if (WIFEXITED(status))
				info->exit_status = WEXITSTATUS(status);
			else
				info->exit_status = 0;
		}
	}
}
