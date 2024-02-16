/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:03:51 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/16 10:05:52 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST.h"

void	syntax_error_tokenizer(char *string, t_token **list)
{
	printf("syntax error near unexpected token: `%s`\n", string);
	free(string);
	free_tokens(list);
}

void	syntax_error_parser(char *string, t_token **list)
{
	printf("parse error near unexpected token: `%s`\n", string);
	free_tokens(list);
}
