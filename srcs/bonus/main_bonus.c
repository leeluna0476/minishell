/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:09:40 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:37:34 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "env_bonus.h"
#include "structures_bonus.h"
#include "execute_bonus.h"
#include "expand_bonus.h"
#include "parser_bonus.h"
#include "redirection_bonus.h"
#include "signal_handler_bonus.h"

void	input_handler(void)
{
	ft_putstr_fd("\e7", STDOUT_FILENO);
	signal_readline();
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

int	main(int ac, char *av[], char *envp[])
{
	char		*str;
	t_env_pack	pack;
	int			exitcode;

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
	exitcode = get_exitstat(&pack);
	free_envs(pack.origin_head);
	return (exitcode);
}
