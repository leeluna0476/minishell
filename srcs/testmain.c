/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/20 00:49:48 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "readline/readline.h"
#include "readline/history.h"
#include <fcntl.h>
#include <unistd.h>

typedef struct s_pipe t_pipe;

struct s_pipe
{
	t_token	*start;
	t_token	*end;
	t_pipe	*prev;
	t_pipe	*next;
};

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
		if (str)
		{
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
		system("leaks -q minishell");
	}
}
