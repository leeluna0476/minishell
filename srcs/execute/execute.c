/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/21 19:36:55 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand.h"
#include "redirection.h"
#include "builtin.h"

void	execute(t_ast *tree, t_env_pack *pack, t_info *info)
{
	info->depths++;
	if (!tree)
		return ;
	else if (tree->type == T_PIPE)
		return (execute_pipe(tree, pack, info, info->depths));
	else if (tree->type == T_OR || tree->type == T_AND)
		return (logical_exp(tree, pack, info));
	else
		return (do_execution(tree, pack, info));
}
// 재귀. 깊이우선탐색. 왼쪽부터 순회.

int	get_exitstat(t_env_pack *pack)
{
	int		res;
	t_env	*target_node;

	target_node = find_env("?", pack);
	return (ft_atoi(target_node->value));
}

void	logical_exp(t_ast *tree, t_env_pack *pack, t_info *info)
{
	info->depths++;
	if (tree->left->type >= T_WORD && tree->left->type <= T_D_GREATER)
	{
		do_execution(tree->left, pack, info);
		ft_wait(info, pack);
	}
	else
		execute(tree->left, pack, info);
	if ((tree->type == T_AND && get_exitstat(pack)) || \
		(tree->type == T_OR && get_exitstat(pack)))
		return ;
	if (tree->right->type >= T_WORD && tree->right->type <= T_D_GREATER)
	{
		do_execution(tree->right, pack, info);
		ft_wait(info, pack);
	}
	else
		execute(tree->right, pack, info);
}

void	execute_pipe(t_ast *tree, t_env_pack *pack, t_info *info, int level)
{
	if (tree->left->type == T_PIPE)
		execute_pipe(tree->left, pack, info, level);
	else
	{
		ft_assert(pipe(info->pipe_fds) != -1, "pipe", 1);
		do_execution(tree->left, pack, info);
	}
	ft_assert(pipe(info->pipe_fds) != -1, "pipe", 1);
	do_execution(tree->right, pack, info);
	if (info->depths == level)
		ft_wait(info, pack);
}

void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info)
{
	t_cmd	*cmd;
	t_redir	*temp;

	cmd = build_cmd_pack(tree, pack);
	if (scan_n_set_redirs(cmd, pack))
		return (free_cmd(cmd));
	// info->depths == 1이 왜 있어야 하는지 모르겠음.
	if (/*info->depths == 1 && */solo_builtin(cmd, pack) != -1)
		return (free_cmd(cmd));
	if (cmd->c_args)
		execute_cmd(cmd, pack, info);
	temp = cmd->all_redirs;
	return (free_cmd(cmd));
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
	ft_assert(info->last_pid != -1, "fork error\n", 1);
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
