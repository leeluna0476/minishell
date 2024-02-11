/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:17 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/11 19:01:35 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute(t_ast *tree)
{
	if (!tree)
		return (-1);
	if (tree->left)
		execute(tree->left);
	if (tree->right)
		execute(tree->right);
}
// 트리 출력. 깊이우선탐색. 왼쪽부터 순회.

void	print_ast(t_ast *ast)
{
	t_token	*curr;

	if (!ast)
		return ;
	curr = ast->start;
	while (curr && curr <= ast->end)
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
	printf("\n");
	if (ast->left)
		print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
}
