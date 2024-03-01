/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:03:51 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/01 10:10:57 by seojilee         ###   ########.fr       */
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
	ft_putstr_fd("syntax error near unclosed quote: `", STDERR_FILENO);
	ft_putstr_fd(string, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(string);
	free_tokens(list);
}

// 파싱 단계에서 오류가 발생하면 오류 메세지와 함께 문제 토큰을 출력.
void	syntax_error_parser(char *string, t_token **list)
{
	ft_putstr_fd("syntax error near unexpected token: ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(string, STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_tokens(list);
}
