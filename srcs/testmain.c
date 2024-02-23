/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/23 17:29:09 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "exec_structures.h"
#include "execute.h"
#include "expand.h"
#include "parser.h"
#include "redirection.h"
#include "parse_struct.h"
#include "parse_define.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "signal_handler.h"
#include <fcntl.h>
#include <unistd.h>

void	set_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->pipe_fds[1] = 1;
	info->redir_fds[1] = 1;
}

void	input_handler(void)
{
	ft_putstr_fd("\e7", STDOUT_FILENO);
	signal_event();
}

void	set_exit(t_env_pack *pack, int code)
{
	char *exit_code_str;

	exit_code_str = ft_itoa(code);
	add_env_node(pack, "?", exit_code_str);
	free(exit_code_str);
}

void	run_minishell(char *str, t_env_pack *pack)
{
	t_token	*tokens;
	t_ast	*ast;
	t_info	info;

	tokens = tokenizer(str);
	if (tokens)
	{
		ast = init_ast(tokens);
		generate_ast(&ast, ast->start, ast->end);
		if (!(ast->error))
		{
			set_info(&info);
			execute(ast, pack, &info);
		}
		else
		{
			syntax_error_parser(ast->error, &tokens);
			set_exit(pack, 258);
		}
		free_tokens(&tokens);
		free_ast(&ast);
	}
	else
		set_exit(pack, 258);
}

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_env_pack	pack;

	(void)ac;
	(void)av;
	build_envp(&pack, envp);
	rl_event_hook = (rl_hook_func_t *)input_handler;
	while (42)
	{
		str = get_line(PROMPT, &pack);
		if (!str)
			break ;
		if (str[0])
		{
			add_history(str);
			run_minishell(str, &pack);
		}
		free(str);
	}
	ft_putstr_fd("\e8\e[B\e[Aexit\n", STDOUT_FILENO);
	return (get_exitstat(&pack));
}
//	print_ast(ast);
