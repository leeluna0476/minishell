/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:07:31 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/16 13:24:24 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*path_join(char *path, char *arg)
{
	char	*temp;
	char	*out;

	temp = ft_strjoin(path, "/");
	out = ft_strjoin(temp, arg);
	free(temp);
	return (out);
}

void	exec_parent(int *fds, int *tmp_fds, int idx)
{
	if (tmp_fds[0] > 2)
		close(tmp_fds[0]);
	if (tmp_fds[1] > 2)
		close(tmp_fds[1]);
	if (idx != 0 && fds[2])
		close(fds[2]);
	if (fds[1] != 1)
		close(fds[1]);
	fds[2] = fds[0];
}

int	ft_wait(int idx, t_cmd *cmds_head, int last_pid)
{
	int		status;
	int		exit_num;

	exit_num = g_exit_status;
	while (idx--)
	{
		if (waitpid(-1, &status, 0) == last_pid)
		{
			if (WIFSIGNALED(status))
				exit_num = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				exit_num = WEXITSTATUS(status);
		}
	}
	unlink_files(cmds_head);
	return (exit_num);
}
