/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:03:51 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 13:18:10 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 파싱 단계에서 오류가 발생하면 문제 토큰을 오류 항목으로 지정.
void	set_parse_error(t_ast *ast, char *string)
{
	if (ast->error)
		free(ast->error);
	ast->error = ft_strdup(string);
}

// 토큰화 단계에서 오류가 발생하면 오류 메세지와 함께 문제 토큰을 출력.
void	syntax_error_tokenizer(char *string, t_token **list)
{
	printf("syntax error near unexpected token: `%s`\n", string);
	free(string);
	free_tokens(list);
}

// 파싱 단계에서 오류가 발생하면 오류 메세지와 함께 문제 토큰을 출력.
void	syntax_error_parser(char *string, t_token **list)
{
	printf("parse error near unexpected token: `%s`\n", string);
	free_tokens(list);
}
