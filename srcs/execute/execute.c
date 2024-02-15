/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youwin0802 <youwin0802@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/15 14:58:30 by youwin0802       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand.h"
#include "redirection.h"
#include "builtin.h"

void	execute(t_ast *tree, t_env_pack *pack, int level, int *fds)
{
	if (!tree)
		return ;
	else if (tree->type == T_PIPE)
		return (execute_pipe(tree, pack, level, fds));		// TODO
	else if (tree->type == T_OR || tree->type == T_AND)
		return /*(logical_expression(tree, pack, level))*/;	// TODO
	else
		do_execution(tree, pack, level, fds);
	execute(tree->left, pack, level + 1, fds);
	execute(tree->right, pack, level + 1, fds);
}
// 트리 출력. 깊이우선탐색. 왼쪽부터 순회.

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

void	execute_pipe(t_ast *tree, t_env_pack *pack, int level, int *fds)
{
	if (!fds)
		fds = build_new_fds();
	if (tree->left->type != (T_AND || T_OR || T_PIPE))
		do_execution(tree->left, pack, level + 1, fds);
	else
		execute(tree->left, pack, level + 1, fds);
	if (tree->right->type != (T_AND || T_OR || T_PIPE))
		do_execution(tree->right, pack, level + 1, fds);
	else
		execute(tree->right, pack, level + 1, fds);
}

pid_t	execute_cmd(t_cmd *cmd, t_env_pack *envs, int *pipe_fds)
{
	int		redir_fds[2];
	pid_t	pid;

	redir_fds[0] = 0;		// 초깃값 세팅
	redir_fds[1] = 1;		// 초깃값 세팅2
	set_fd(cmd, pipe_fds, redir_fds);
	// signal(SIGINT, SIG_IGN);
	// signal(SIGINT, exec_handler);
	pid = fork();
	if (pid == -1)
	{
		ft_printf("fork error!\n");
		g_exit_status = 1;
	}
	if (pid == 0)
	{
		if (cmd->c_args)
		{
			ft_dup2(pipe_fds, redir_fds);
			ft_execve(cmd, envs);				//TODO
		}
	}
	else
		exec_parent(pipe_fds, redir_fds);		//TODO
	return (pid);
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
	do_execve(cmd->c_args, envs, envp);
}

void	ft_dup2(int *pipe_fds, int *redir_fds)
{
	if (redir_fds[0] != 0)
	{
		dup2(redir_fds[0], STDIN_FILENO);
		close(redir_fds[0]);
	}
	if (redir_fds[1] != 1)
	{
		dup2(redir_fds[1], STDOUT_FILENO);
		close(redir_fds[1]);
	}
	if (pipe_fds && pipe_fds[0])
		close(pipe_fds);
	if (pipe_fds && pipe_fds[1] != 1)
		close(pipe_fds[1]);
	free(pipe_fds);
}

void	do_execution(t_ast *tree, t_env_pack *pack, int level, int *fds)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = build_cmd_pack(tree, pack);
	if (scan_n_set_redirs(cmd, pack))
		return /*(free_cmd(tree))*/;		// TODO
	if (level == 0 && solo_builtin(cmd, pack))
		return /*(free_cmd(tree))*/;
	pid = execute_cmd(cmd, pack, fds);
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
