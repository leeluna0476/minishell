/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:14:15 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:55:05 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_bonus.h"
#include "redirection_bonus.h"
#include "expand_bonus.h"
#include "builtin_bonus.h"
#include "parser_bonus.h"

void	set_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->pipe_fds[1] = 1;
	info->redir_fds[1] = 1;
}

t_cmd	*build_cmd_pack(t_ast *tree, t_env_pack *pack)
{
	t_cmd	*cmd;
	t_token	*cur;
	char	**limiter;

	cur = tree->start;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit (1);
	while (cur && cur->prev != tree->end)
	{
		if (cur->prev && cur->prev->type == T_D_LESSER)
		{
			limiter = add_str(0, ft_strdup(cur->string));
			limiter = add_str(limiter, trim_quotes(cur->string));
			append_redir(&cmd, cur->prev->type, limiter);
		}
		else if (cur->prev && is_redirection(cur->prev->type))
			append_redir(&cmd, cur->prev->type, \
				expand(ft_strdup(cur->string), pack, 1));
		else if (cur->type == T_WORD)
			cmd->c_args = merge_strs(cmd->c_args, \
			expand(ft_strdup(cur->string), pack, 0));
		cur = cur->next;
	}
	return (cmd);
}

void	ft_execve(t_cmd *cmd, t_env_pack *envs)
{
	char	**envp;

	if (exec_builtin(cmd->c_args, envs) != -1)
		exit (0);
	envp = make_envp(envs);
	if (is_route(cmd->c_args[0]))
	{
		if (execve(cmd->c_args[0], cmd->c_args, envp) < 0)
		{
			if (is_dir(cmd->c_args[0]))
				errno = EISDIR;
			if (errno == EISDIR || errno == ENOTDIR || errno == EACCES)
				ft_perror(cmd->c_args[0], 126);
			else if (access(cmd->c_args[0], F_OK))
				ft_perror(cmd->c_args[0], 128);
			exit(0);
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
		ft_perror(args[0], 128);
	path_split = ft_split(path->value, ':');
	i = 0;
	while (path_split && path_split[i])
	{
		relative_path = path_join(path_split[i], args[0]);
		if (access(relative_path, X_OK) == 0 && !is_dir(relative_path))
			ft_assert(execve(relative_path, args, envp) != -1, args[0], 1);
		free(relative_path);
		free(path_split[i]);
		i++;
	}
	free(path_split);
	ft_perror(args[0], 127);
}

void	free_cmd(t_cmd *cmd)
{
	t_redir	*temp;
	t_redir	*next;

	if (cmd->c_args)
		split_free(cmd->c_args);
	temp = cmd->all_redirs;
	while (temp)
	{
		next = temp->next;
		if (temp->type == T_D_LESSER)
			unlink(temp->filename[1]);
		split_free(temp->filename);
		free(temp);
		temp = next;
	}
	free(cmd);
}
