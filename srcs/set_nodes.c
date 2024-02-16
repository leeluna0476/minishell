/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:53:02 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 10:58:29 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

// 현재 노드에 start, end 할당.
// 괄호 짝이 맞지 않는 경우는 에러 처리. 예: (ls
// 괄호가 중첩되는 경우는 에러 처리. 예: ((ls))
void	set_start_end(t_ast **ast, t_token *start, t_token *end)
{
	t_token	*err_token;
	int		single_pair;

	single_pair = check_if_single_pair(start, end);
	*ast = ft_calloc(1, sizeof(t_ast));
	if (*ast)
	{
		err_token = check_bracket(start, end);
		if (!err_token)
			err_token = check_pipe_in_bracket(start, end);
		remove_bracket(&start, &end);
		if (err_token)
			(*ast)->error = ft_strdup(err_token->string);
		else if (single_pair && check_if_single_pair(start, end) \
				&& start->type == T_OPEN_BRACKET \
				&& end->type == T_CLOSE_BRACKET)
			(*ast)->error = ft_strdup(start->string);
		(*ast)->start = start;
		(*ast)->end = end;
	}
}

// simple command에서 리다이렉션에 해당하는 부분을 모아서 연결리스트로 만듦.
//t_token	*set_redirs(t_ast **ast, t_token *start, t_token *end)
//{
//	t_token	*node;
//	t_token	*redirs;
//	t_token	*curr;
//
//	redirs = NULL;
//	curr = start;
//	while (curr && curr <= end)
//	{
//		if (is_redirection(curr->type))
//		{
//			node = new_token(curr->string, curr->type);
//			add_token(&redirs, node);
//			if (check_redirection_error(*ast, curr))
//			{
//				free_tokens(&redirs);
//				return (NULL);
//			}
//			curr = curr->next;
//			node = new_token(curr->string, curr->type);
//			add_token(&redirs, node);
//		}
//		if (curr)
//			curr = curr->next;
//	}
//	return (redirs);
//}
//
//// simple command에서 일반 명령어(인자) 해당하는 부분을 모아서 연결리스트로 만듦.
//t_token	*set_commands(t_token *start, t_token *end)
//{
//	t_token	*node;
//	t_token	*cmds;
//	t_token	*curr;
//
//	cmds = NULL;
//	curr = start;
//	while (curr && curr <= end)
//	{
//		if (!is_redirection(curr->type))
//		{
//			node = new_token(curr->string, curr->type);
//			add_token(&cmds, node);
//		}
//		else
//		curr = curr->next;
//		curr = curr->next;
//	}
//	return (cmds);
//}
//
//// simple command에서 리다이렉션이 있는지 확인 후, 있다면 일반 명령어와 분할, 없다면 유지.
//void	set_cmds_redirs(t_ast **ast, t_token *start, t_token *end)
//{
//	t_token	*redirs;
//	t_token	*cmds;
//
//	redirs = set_redirs(ast, start, end);
//	if (redirs)
//	{
//		cmds = set_commands(start, end);
//		if (cmds)
//		{
//			set_start_end(&((*ast)->left), redirs, last_token(redirs));
//			if ((*ast)->left)
//				(*ast)->left->type = redirs->type;
//			set_start_end(&((*ast)->right), cmds, last_token(cmds));
//			if ((*ast)->right)
//				(*ast)->right->type = T_CMD;
//		}
//		else
//			free_tokens(&redirs);
//	}
//}
