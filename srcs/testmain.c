/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/23 09:29:31 by seojilee         ###   ########.fr       */
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

void	update_cursor(void)
{
	ft_putstr_fd("\e7", STDOUT_FILENO);
	signal_event();
}

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_token	*tokens;
	t_ast	*ast;
	t_env_pack	pack;
	t_info		info;

	(void)ac;
	(void)av;
	build_envp(&pack, envp);
	rl_event_hook = (rl_hook_func_t *)update_cursor;
	while (42)
	{
		str = get_line(PROMPT);
		if (!str)
			break ;
		if (str[0])
			add_history(str);
		tokens = tokenizer(str);
		if (tokens)
		{
			ast = init_ast(tokens);
			generate_ast(&ast, ast->start, ast->end);
			if (!(ast->error))
			{
				set_info(&info);
				execute(ast, &pack, &info);
				while (waitpid(-1, NULL, WNOHANG) != -1);
			}
			else
				syntax_error_parser(ast->error, &tokens);
			free_tokens(&tokens);

			free_ast(&ast);
		}
		free(str);
		// system("leaks minishell");
	}
	ft_putstr_fd("\e8\e[B\e[Aexit\n", STDOUT_FILENO);
}
//	print_ast(ast);
//	system("leaks -q minishell");
