/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 13:38:43 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand.h"
#include "redirection.h"
#include "builtin.h"

void	execute(t_ast *tree, t_env_pack *pack, t_info *info)
{
	if (!tree)
		return ;
	else if (tree->type == T_PIPE)
		return (execute_pipe(tree, pack, info, info->depths));
	else if (tree->type == T_OR || tree->type == T_AND)
		return (logical_exp(tree, pack, info));
	else
		do_execution(tree, pack, info);
	info->depths++;
	execute(tree->left, pack, info);
	execute(tree->right, pack, info);
}
// 재귀. 깊이우선탐색. 왼쪽부터 순회.

void	logical_exp(t_ast *tree, t_env_pack *pack, t_info *info)
{
	info->depths++;
	if (tree->left->type != (T_AND || T_OR || T_PIPE))
	{
		do_execution(tree->left, pack, info);
		ft_wait(info);
	}
	else
		execute(tree->left, pack, info);
	if (tree->type == T_AND && g_exit_status != 0)
		return ;
	if (tree->right->type != (T_AND || T_OR || T_PIPE))
	{
		do_execution(tree->right, pack, info);
		ft_wait(info);
	}
	else
		execute(tree->right, pack, info);
}

void	execute_pipe(t_ast *tree, t_env_pack *pack, t_info *info, int level)	//depths기록하고 wait하기
{
	if (!info->pipe_fds)
		info->pipe_fds = build_new_fds();
	info->depths++;
	if (tree->left->type != (T_AND || T_OR || T_PIPE))
		do_execution(tree->left, pack, info);
	else
		execute(tree->left, pack, info);
	if (tree->right->type != (T_AND || T_OR || T_PIPE))
		do_execution(tree->right, pack, info);
	else
		execute(tree->right, pack, info);
	if (info->depths == level + 1)
		ft_wait(info);
}

void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info)
{
	t_cmd	*cmd;
	t_redir	*temp;

	cmd = build_cmd_pack(tree, pack);
	if (scan_n_set_redirs(cmd, pack))
		return /*(free_cmd(cmd))*/;		// TODO
	if (info->depths == 0 && solo_builtin(cmd, pack))
		return /*(free_cmd(cmd))*/;
	execute_cmd(cmd, pack, info);
	temp = cmd->all_redirs;
	while (temp)
	{
		if (temp->type == T_D_LESSER)
			unlink(temp->filename[1]);
		temp = temp->next;
	}
}
	// ft_printf("print output cmd structure!\n");
	// if (cmd->in_redirs && cmd->out_redirs)
	// 	ft_printf("redirections:\nin: %s\nout:%s\n", cmd->in_redirs->filename[1], cmd->out_redirs->filename[1]);
	// if (!cmd->c_args)
	// 	return ;
	// ft_printf("command_args:\n");
	// int	i = -1;
	// while (cmd->c_args && cmd->c_args[++i])
	// 	ft_printf("args %d: [%s]\n", i, cmd->c_args[i]);

void	execute_cmd(t_cmd *cmd, t_env_pack *envs, t_info *info)
{
	set_fds(cmd, info);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, exec_handler);
	info->last_pid = fork();
	if (info->last_pid == -1)
	{
		ft_printf("fork error!\n");
		g_exit_status = 1;
	}
	info->fork_num++;
	if (info->last_pid == 0)
	{
		if (cmd->c_args)
		{
			ft_dup2(info);
			ft_execve(cmd, envs);
		}
	}
	else
		exec_parent(info);
}
