/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 15:27:41 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expand.h"
#include "redirection.h"
#include "builtin.h"

void	execute(t_ast *tree, t_env_pack *pack, int level)
{
	if (!tree)
		return ;
	if (tree->type == T_PIPE)
		return /*(execute_pipe(tree, pack, level))*/;		// TODO
	if (tree->type == T_OR || tree->type == T_AND)
		return /*(logical_expression(tree, pack, level))*/;	// TODO
	if (!tree->left && !tree->right)
	{
		do_execution(tree, pack, level);
	}
	execute(tree->left, pack, level + 1);
	execute(tree->right, pack, level + 1);
}
// 트리 출력. 깊이우선탐색. 왼쪽부터 순회.

void	do_execution(t_ast *tree, t_env_pack *pack, int level)
{
	t_cmd	*cmd;

	cmd = build_cmd_pack(tree, pack);
	if (scan_n_set_redirs(cmd, pack))
		return /*(free_cmd(tree))*/;		// TODO


	// ft_printf("print output cmd structure!\n");
	// if (cmd->in_redirs && cmd->out_redirs)
	// 	ft_printf("redirections:\nin: %s\nout:%s\n", cmd->in_redirs->filename[1], cmd->out_redirs->filename[1]);
	// if (!cmd->c_args)
	// 	return ;
	// ft_printf("command_args:\n");
	// int	i = -1;
	// while (cmd->c_args && cmd->c_args[++i])
	// 	ft_printf("args %d: [%s]\n", i, cmd->c_args[i]);


	if (level == 0 && solo_builtin(cmd, pack))
		return /*(free_cmd(tree))*/;
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
