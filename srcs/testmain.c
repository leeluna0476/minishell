/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:09:40 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/24 12:27:26 by seojilee         ###   ########.fr       */
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
#include "signal_handler.h"

void	set_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->pipe_fds[1] = 1;
	info->redir_fds[1] = 1;
}

void	input_handler(void)
{
	ft_putstr_fd("\e7", STDOUT_FILENO);
	signal_readline();
}

void	set_exit(t_env_pack *pack, int code)
{
	char *exit_code_str;

	exit_code_str = ft_itoa(code);
	add_env_node(pack, "?", exit_code_str);
	free(exit_code_str);
}

void	free_inputs(t_token **tokens, t_ast **ast)
{
	free_tokens(tokens);
	free_ast(ast);
}

void	run_minishell(char *str, t_env_pack *pack)
{
	t_token	*tokens;
	t_ast	*ast;
	t_info	info;

	str += remove_space(str);
	tokens = tokenizer(str);
	if (tokens)
	{
		ast = init_ast(tokens);
		generate_ast(&ast, ast->start, ast->end);
		if (!(ast->error))
		{
			set_info(&info);
			execute(ast, pack, &info);
			// 임시 wait.
			while (waitpid(-1, NULL, WNOHANG) != -1);
		}
		else
		{
			syntax_error_parser(ast->error, &tokens);
			set_exit(pack, 258);
		}
		free_inputs(&tokens, &ast);
	}
	else if (!tokens && *str)
		set_exit(pack, 258);
}

void	leaks(void)
{
	system("leaks -q minishell");
}

//	print_ast(ast);
int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_env_pack	pack;

//	atexit(leaks);
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
//		leaks();
	}
	ft_putstr_fd("\e8\e[B\e[Aexit\n", STDOUT_FILENO);
	return (get_exitstat(&pack));
}
