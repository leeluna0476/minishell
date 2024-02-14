/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:33:59 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 15:29:35 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	append_redir(t_cmd **cmd, t_type type, char **fileinfo)
{
	t_redir	*new;
	t_redir	*temp;

	// int	i = -1;
	// if (type == T_LESSER)
	// 	ft_printf("\ntype is <\n");
	// else if (type == T_GREATER)
	// 	ft_printf("\ntype is >\n");
	// else if (type == T_D_GREATER)
	// 	ft_printf("\ntype is >>\n");
	// ft_printf("print fileinfo\n");
	// while (fileinfo && fileinfo[++i])
	// 	ft_printf("[%s] ", fileinfo[i]);
	// ft_printf("\n");

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

	temp = cmd->all_redirs;
	while (temp)
	{
		if (temp->type == T_D_LESSER || temp->type == T_LESSER)
			cmd->in_redirs = temp;
		else if (temp->type == T_D_GREATER || temp->type == T_GREATER)
			cmd->out_redirs = temp;
		if (temp->type == T_D_LESSER)
		{
			if (heredoc(temp, pack))
				return (1);
		}
		temp = temp->next;
	}
	temp = cmd->all_redirs;
	return (open_check(temp));
}

int	open_check(t_redir *temp)
{
	g_exit_status = 1;

	while (temp)
	{
		if (temp->type != T_D_LESSER && split_len(temp->filename) > 2)
		{
			ft_printf("%s: ambiguous redirect\n", temp->filename[0]);
			return (1);
		}
		redir_open(temp);
		if (temp->type != T_D_LESSER && temp->fd < 0)
		{
			if (access(temp->filename[1], F_OK) == 0)
				printf("%s: Permission denied\n", temp->filename[1]);
			else
				printf("%s: No such file or directory\n", temp->filename[1]);
			return (1);
		}
		if (temp->fd > 2)
			close(temp->fd);
		temp = temp->next;
	}
	g_exit_status = 0;
	return (0);
}
