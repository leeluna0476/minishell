/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 12:05:33 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 현재 기호가 리다이렉션 문자인지 확인.
int	is_redirection(t_type type)
{
	return (type == T_LESSER || type == T_GREATER \
	|| type == T_D_LESSER || type == T_D_GREATER);
}

// 트리 초기화.
// 초기 start, end는 토큰의 시작과 끝.
t_ast	*init_ast(t_token *tokens)
{
	t_ast	*ast;

	set_start_end(&ast, tokens, last_token(tokens));
	return (ast);
}

// 트리 출력. 깊이우선탐색. 왼쪽부터 순회.
void	print_ast(t_ast *ast)
{
	t_token	*curr;

	if (!ast)
		return ;
	curr = ast->start;
	while (curr && curr->prev != ast->end)
	{
		printf("[%s] ", curr->string);
		curr = curr->next;
	}
	printf("\n");
	if (ast->left)
		print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
}

// 트리의 각 노드 메모리 해제.
void	free_node(t_ast **node)
{
	free((*node)->error);
	free(*node);
	*node = NULL;
}

// 트리 메모리 해제.
void	free_ast(t_ast **ast)
{
	if (*ast && (*ast)->left)
		free_ast(&((*ast)->left));
	if (*ast && (*ast)->right)
		free_ast(&((*ast)->right));
	free_node(ast);
}
