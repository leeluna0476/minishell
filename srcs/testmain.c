/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/21 13:02:14 by seojilee         ###   ########.fr       */
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
//#include "structures.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "signal_handler.h"
#include <fcntl.h>
#include <unistd.h>

void	set_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->pipe_fds[1] = 1;
	info->redir_fds[1] = 1;
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
	set_info(&info);
	while (42)
	{
		str = get_line("minishell> ");
		if (str)
		{
			if (str[0])
				add_history(str);
			tokens = tokenizer(str);
			if (tokens)
			{
				ast = init_ast(tokens);
				generate_ast(&ast, ast->start, ast->end);
				if (!(ast->error))
				{
					execute(ast, &pack, &info);
					while (waitpid(-1, NULL, WNOHANG) != -1);
				}
				else
					syntax_error_parser(ast->error, &tokens);
				free_tokens(&tokens);
				free_ast(&ast);
			}
			free(str);
		}
		else
			exit(0);
	}
}
//	print_ast(ast);
//	system("leaks -q minishell");
