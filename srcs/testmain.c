/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/23 12:56:45 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "signal_handler.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_token	*tokens;
	t_ast	*ast;

	(void)ac;
	(void)av;
	(void)envp;
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
					print_ast(ast);
				else
					syntax_error_parser(ast->error, &tokens);
				free_tokens(&tokens);
				free_ast(&ast);
			}
			free(str);
		}
		else
			exit(0);
//		system("leaks -q minishell");
	}
}
