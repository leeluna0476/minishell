/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 09:33:59 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/20 07:25:24 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "env.h"

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

int	scan_n_set_redirs(t_cmd *cmd, t_env_pack *pack)
{
	t_redir	*temp;
	int		exit_code;
	char	*exit_code_str;

	temp = cmd->all_redirs;
	exit_code = 0;
	while (temp && exit_code == 0)
	{
		if (temp->type == T_D_LESSER || temp->type == T_LESSER)
			cmd->in_redirs = temp;
		else if (temp->type == T_D_GREATER || temp->type == T_GREATER)
			cmd->out_redirs = temp;
		if (temp->type == T_D_LESSER)
			exit_code = heredoc(temp, pack);
		temp = temp->next;
	}
	temp = cmd->all_redirs;
	if (exit_code || open_check(temp))
	{
		exit_code_str = ft_itoa(exit_code);
		add_env_node(pack, "?", exit_code_str);
		free(exit_code_str);
	}
	return (0);
}

int	open_check(t_redir *temp)
{
	while (temp)
	{
		if (temp->type != T_D_LESSER && split_len(temp->filename) > 2)
		{
			ft_putstr_fd(temp->filename[0], STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			return (1);
		}
		redir_open(temp);
		if (temp->type != T_D_LESSER && temp->fd < 0)
		{
			ft_putstr_fd(temp->filename[1], STDERR_FILENO);
			if (access(temp->filename[1], F_OK) == 0)
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			else
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (1);
		}
		if (temp->fd > 2)
			close(temp->fd);
		temp = temp->next;
	}
	return (0);
}
