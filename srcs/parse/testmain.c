#include "AST.h"
#include "readline/readline.h"
#include "readline/history.h"

int	main(int ac, char *av[], char *envp[])
{
	char	*str;
	t_token	*tokens;
	t_ast	*ast;
	t_env_pack	env;

	(void)ac;
	(void)av;
	build_envp(&env, envp);
	while (42)
	{
		str = readline("minishell> ");
		tokens = tokenizer(str);
		if (tokens)
		{
			ast = init_ast(tokens);
			generate_ast(&ast, ast->start, ast->end);
			if (!(ast->error))
			{
				print_ast(ast);
				execute(ast, &env, 0);
			}
			else
				syntax_error_parser(ast->error, &tokens);
			free_tokens(&tokens);
			free_ast(&ast);
		}
		free(str);
	}
}
