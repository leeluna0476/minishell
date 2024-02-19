/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:14:15 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 13:44:39 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "redirection.h"
#include "expand.h"
#include "builtin.h"

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
				ft_perror(cmd->c_args[0], 126);
			else
				ft_perror(cmd->c_args[0], 1);
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
		ft_perror(args[0], 1);
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

void	ft_perror(char *str, int exit_num)
{
	if (exit_num == 126)
		ft_printf("minishell: %s: is a directory\n", str);
	else if (exit_num == 127)
		ft_printf("minishell: %s: command not found\n", str);
	else if (exit_num == 128)
	{
		ft_printf("minishell: %s: No such file or directory\n", str);
		exit_num--;
	}
	else
		perror(str);
	exit(exit_num);
}
