/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 11:34:54 by yusekim          ###   ########.fr       */
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
		return (execute_pipe(tree, pack, info, info->depths));		// TODO
	else if (tree->type == T_OR || tree->type == T_AND)
		return /*(logical_exp(tree, pack, info), info->depths)*/;	// TODO
	else
		do_execution(tree, pack, info);
	info->depths++;
	execute(tree->left, pack, info);
	execute(tree->right, pack, info);
}
// 트리 출력. 깊이우선탐색. 왼쪽부터 순회.

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

void	execute_cmd(t_cmd *cmd, t_env_pack *envs, t_info *info)
{
	set_fd(cmd, info);
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

void	exec_parent(t_info *info)
{
	if (info->redir_fds[0] > 2)
		close(info->redir_fds[0]);
	if (info->redir_fds[1] > 2)
		close(info->redir_fds[1]);
	if (info->fork_num != 0 && info->pipe_fds[2])
		close(info->pipe_fds[2]);
	if (info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
	info->pipe_fds[2] = info->pipe_fds[0];
}

void	ft_execve(t_cmd *cmd, t_env_pack *envs)
{
	char	**envp;

	if (exec_builtin(cmd->c_args, envs))
		exit (0);
	envp = make_envp(envs);
	if (is_route(cmd->c_args[0]))
	{
		if (execve(cmd->c_args[0], cmd->c_args, envp) < 0)
		{
			if (is_dir(cmd->c_args[0]))
				exit(1);// ft_perror(cmd->c_args[0], 126);	//TODO
			else
				exit(1);//ft_perror(cmd->c_args[0], 1);
		}
	}
	relative_execve(cmd->c_args, envs, envp);
}

void	relative_execve(char **args, t_env_pack *envs, char **envp)
{
	char	**path_split;
	int		i;
	char	*relative_path;
	t_env	*path;

	path = find_env("PATH", envs);
	if (!path)
		exit(1); // ft_perror(no such file or directory)
	path_split = ft_split(path->value, ':');
	i = 0;
	while (path_split && path_split[i])
	{
		relative_path = path_join(path_split[i], args[0]);
		if (access(relative_path, X_OK) == 0)
		{
			if (execve(relative_path, args, envp) < 0)
				exit (1); // ftperror
		}
		free(relative_path);
		free(path_split[i]);
		i++;
	}
	free(path_split);
	exit(1);	// ftperror()
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
		close(info->pipe_fds);
	if (info->pipe_fds && info->pipe_fds[1] != 1)
		close(info->pipe_fds[1]);
	free(info->pipe_fds);
}

void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info)
{
	t_cmd			*cmd;

	cmd = build_cmd_pack(tree, pack);
	if (scan_n_set_redirs(cmd, pack))
		return /*(free_cmd(tree))*/;		// TODO
	if (info->depths == 0 && solo_builtin(cmd, pack))
		return /*(free_cmd(tree))*/;
	execute_cmd(cmd, pack, info);
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


t_cmd	*build_cmd_pack(t_ast *tree, t_env_pack *pack)
{
	t_cmd	*cmd;
	t_token	*cur;
	char	**limiter;

	cur = tree->start;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit (1);
	while (cur && cur <= tree->end)
	{
		if (cur->prev && cur->prev->type == T_D_LESSER)
		{
			limiter = add_str(0, cur->string);
			limiter = add_str(limiter, trim_quotes(cur->string));
			// ft_printf("token data: %s\n", cur->string);		test code
			append_redir(&cmd, cur->prev->type, limiter);
		}
		else if (cur->prev && cur->prev->type > T_PIPE)
			append_redir(&cmd, cur->prev->type, expand(ft_strdup(cur->string), pack, 1));
		else if (cur->type == T_WORD)
		{
			cmd->c_args = merge_strs(cmd->c_args, expand(ft_strdup(cur->string), pack, 0));
		}
		cur = cur->next;
	}
	return (cmd);
}
