/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:07:31 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 13:11:18 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	set_fds(t_cmd *cmd, t_info *info)
{
	if (cmd->in_redirs)
	{
		info->redir_fds[0] = open(cmd->in_redirs->filename[1], O_RDONLY);
		if (info->redir_fds[0] == -1)
			ft_printf("open error[%s]\n", cmd->in_redirs->filename[1]); // exit status = 1
	}
	else if (info->pipe_fds)
		info->redir_fds[0] = info->pipe_fds[2];
	if (cmd->out_redirs)
	{
		if (cmd->out_redirs->type == T_D_GREATER)
			info->redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			info->redir_fds[1] = open(cmd->out_redirs->filename[1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (info->redir_fds[1] == -1)
			ft_printf("open error [%s]\n", cmd->out_redirs->filename[1]);
	}
	else if (info->pipe_fds)
		info->redir_fds[1] = info->pipe_fds[1];
}

int	*build_new_fds(void)
{
	int	*new_fds;

	new_fds = malloc(sizeof(int) * 3);
	if (!new_fds)
		exit(1);
	new_fds[2] = 0;
	if (pipe(new_fds) == -1)
		exit (1);
	return (new_fds);
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
	if (info->pipe_fds && info->pipe_fds[0])
		close(info->pipe_fds[0]);
	if (info->pipe_fds && info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
	free(info->pipe_fds);
}

void	ft_wait(t_info *info)
{
	int		status;
	int		exit_num;

	exit_num = g_exit_status;
	while (info->fork_num--)
	{
		if (waitpid(-1, &status, 0) == info->last_pid)
		{
			if (WIFSIGNALED(status))
				exit_num = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				exit_num = WEXITSTATUS(status);
		}
	}
	g_exit_status = exit_num;
	return ;
}
