#include "AST.h"

// 어떤 토큰을 기준으로 가지를 나눌지.
// 괄호를 만나면 짝을 만날 때까지 이동.
// 우선순위: 1. (), 2. &&, ||, 3. |
t_token	*get_center(t_ast *ast, t_token *start, t_token *end)
{
	t_token	*curr;
	int		flag;

	curr = end;
	while (curr && curr >= start)
	{
		if (curr->type == T_CLOSE_BRACKET)
		{
			flag = 1;
			curr = curr->prev;
			while (flag && curr)
			{
				if (curr->type == T_OPEN_BRACKET)
					flag--;
				else if (curr->type == T_CLOSE_BRACKET)
					flag++;
				curr = curr->prev;
			}
		}
		if ((curr >= start && (curr->type == T_AND || curr->type == T_OR)))
		{
			check_center_error(ast, curr);
			return (curr);
		}
		if (curr >= start)
			curr = curr->prev;
	}
	curr = end;
	while (curr && curr >= start)
	{
		if (curr->type == T_PIPE)
		{
			check_center_error(ast, curr);
			return (curr);
		}
		curr = curr->prev;
	}
	return (NULL);
}

// 가지 분할의 기준점이 되는 논리 연산자 또는 파이프를 확인.
// 기준점이 없다면 simple command.
void	generate_ast(t_ast **ast, t_token *start, t_token *end)
{
	t_token	*center;

	center = get_center(*ast, start, end);
	if (check_error(*ast))
		return ;
	if (center)
	{
		(*ast)->type = center->type;

		set_start_end(&((*ast)->left), start, center->prev);
		generate_ast(&((*ast)->left), (*ast)->left->start, (*ast)->left->end);
		if (check_error(*ast))
			return ;

		set_start_end(&((*ast)->right), center->next, end);
		generate_ast(&((*ast)->right), (*ast)->right->start, (*ast)->right->end);
		if (check_error(*ast))
			return ;
	}
	else
	{
		(*ast)->type = T_WORD;
		set_cmds_redirs(ast, start, end);
		check_error(*ast);
	}
}

// 트리 초기화.
// 초기 start, end는 토큰의 시작과 끝.
t_ast	*init_ast(t_token *tokens)
{
	t_ast	*ast;

	set_start_end(&ast, tokens, last_token(tokens));
	return (ast);
}

void	syntax_error_parser(char *string, t_token **list)
{
	// print error
	printf("parse error near unexpected token: `%s`\n", string);
	free_tokens(list);
}

void	leaks(void)
{
	system("leaks -q a.out");
}

//int	main(void)
//{
//	t_ast	*ast;
//	t_token	*tokens;
//
//	atexit(leaks);
//	tokens = tokenizer("ls && (ls && ls && ( ls && ls ) && (ls && ls) && ls) && ls");
//
//	if (tokens)
//	{
//		ast = init_ast(tokens);
//		if (ast)
//		{
//			generate_ast(&ast, ast->start, ast->end);
//
//			if (!(ast->error))
//			{
//				print_ast(ast);
//				printf("\n");
//			}
//			else
//				syntax_error_parser(ast->error, &tokens);
//
//			free_ast(&ast);
//		}
//		free_tokens(&tokens);
//	}
//}
