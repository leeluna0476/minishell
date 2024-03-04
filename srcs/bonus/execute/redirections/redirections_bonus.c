/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:33:59 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:36:03 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_bonus.h"
#include "env_bonus.h"

void	append_redir(t_cmd **cmd, t_type type, char **fileinfo)
{
	t_redir	*new;
	t_redir	*temp;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		exit(1);
	new->type = type;
	new->filename = fileinfo;
	if (!(*cmd)->all_redirs)
		(*cmd)->all_redirs = new;
	else
	{
		temp = (*cmd)->all_redirs;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	scan_n_set_redirs(t_cmd *cmd, t_env_pack *pack)
{
	t_redir	*temp;
	int		exit_code;

	temp = cmd->all_redirs;
	exit_code = 0;
	while (temp && exit_code == 0)
	{
		if (temp->type == T_D_LESSER || temp->type == T_LESSER)
			cmd->in_redirs = temp;
		else if (temp->type == T_D_GREATER || temp->type == T_GREATER)
			cmd->out_redirs = temp;
		if (temp->type == T_D_LESSER)
			exit_code = heredoc(temp, pack, get_filename());
		temp = temp->next;
	}
	if (exit_code)
		return (exit_code);
	temp = cmd->all_redirs;
	open_check(temp, &exit_code);
	return (exit_code);
}

int	open_check(t_redir *temp, int *exit_code)
{
	while (temp)
	{
		if (temp->type != T_D_LESSER && split_len(temp->filename) > 2)
		{
			ft_putstr_fd(temp->filename[0], STDERR_FILENO);
			ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
			*exit_code = 1;
			return (1);
		}
		redir_open(temp);
		if (temp->type != T_D_LESSER && temp->fd < 0)
		{
			ft_putstr_fd(temp->filename[1], STDERR_FILENO);
			if (access(temp->filename[1], F_OK) == 0)
				ft_putendl_fd(": Permission denied", STDERR_FILENO);
			else
				ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			*exit_code = 1;
			return (1);
		}
		if (temp->fd > 2)
			close(temp->fd);
		temp = temp->next;
	}
	return (0);
}
