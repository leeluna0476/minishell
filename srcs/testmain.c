/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 08:53:39 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"
#include "readline/readline.h"
#include "readline/history.h"

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
		str = readline("minishell> ");
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
//		system("leaks -q minishell");
	}
}
