/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/26 18:01:36 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand.h"
#include "redirection.h"
#include "builtin.h"
#include "signal_handler.h"

void	execute(t_ast *tree, t_env_pack *pack, t_info *info)
{
	if (!tree)
		return ;
	else if (tree->type == T_PIPE)
	{
		info->depths++;
		return (execute_pipe(tree, pack, info, info->depths));
	}
	else if (tree->type == T_OR || tree->type == T_AND)
		return (logical_exp(tree, pack, info));
	else
	{
		do_execution(tree, pack, info);
		if (info->fork_num)
			ft_wait(info, pack);
	}

}
// 재귀. 깊이우선탐색. 왼쪽부터 순회.

void	logical_exp(t_ast *tree, t_env_pack *pack, t_info *info)
{
	if (tree->left->type >= T_WORD && tree->left->type <= T_D_GREATER)
	{
		do_execution(tree->left, pack, info);
		if (info->fork_num)
			ft_wait(info, pack);
	}
	else
	{
		set_info(info);
		execute(tree->left, pack, info);
	}
	if ((tree->type == T_AND && get_exitstat(pack)) || \
		(tree->type == T_OR && !get_exitstat(pack)))
		return ;
	if (tree->right->type >= T_WORD && tree->right->type <= T_D_GREATER)
	{
		do_execution(tree->right, pack, info);
		ft_wait(info, pack);
	}
	else
	{
		set_info(info);
		execute(tree->right, pack, info);
	}
}

void	execute_pipe(t_ast *tree, t_env_pack *pack, t_info *info, int level)
{
	int		temp_depths;

	temp_depths = info->depths;
	if (tree->left->type == T_PIPE)
	{
		info->depths++;
		execute_pipe(tree->left, pack, info, level);
	}
	else
	{
		ft_assert(pipe(info->pipe_fds) != -1, "pipe", 1);
		do_execution(tree->left, pack, info);
	}
	if (temp_depths != level)
		ft_assert(pipe(info->pipe_fds) != -1, "pipe", 1);
	do_execution(tree->right, pack, info);
	if (!(info->fork_num))
		return ;
	if (temp_depths == level)
		ft_wait(info, pack);
}

void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info)
{
	t_cmd	*cmd;

	cmd = build_cmd_pack(tree, pack);
	info->prev_signal += scan_n_set_redirs(cmd, pack);
	if (info->prev_signal)
	{
		add_env_node(pack, "?", "1");
		return (free_cmd(cmd));
	}
	if (info->depths == 0 && solo_builtin(cmd, pack) != -1)
		return (free_cmd(cmd));
	if (info->prev_signal == 0)
		execute_cmd(cmd, pack, info);
	return (free_cmd(cmd));
}

void	execute_cmd(t_cmd *cmd, t_env_pack *envs, t_info *info)
{
	set_fds(cmd, info);
	signal_ign();
	info->last_pid = fork();
	ft_assert(info->last_pid != -1, "fork error\n", 1);
	info->fork_num++;
	if (info->last_pid == 0)
	{
		signal_dfl();
		if (cmd->c_args)
		{
			ft_dup2(info);
			ft_execve(cmd, envs);
		}
		exit(0);
	}
	else
		exec_parent(info);
}
