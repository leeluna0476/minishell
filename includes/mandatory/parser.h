/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:06:48 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/01 10:26:39 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "tokenizer.h"

// ast.c
void	generate_ast(t_ast **ast, t_token *start, t_token *end);

// ast_utils.c
int		is_redirection(t_type type);
t_ast	*init_ast(t_token *tokens);
void	print_ast(t_ast *ast);
void	free_node(t_ast **node);
void	free_ast(t_ast **ast);

// bracket.c
int		get_bracket_flag(t_token **start, t_token **end, \
					t_token **first, t_token **last);
int		tokcmp(t_token *token1, t_token *token2);
t_token	*check_bracket(t_token *start, t_token *end);
int		check_if_single_pair(t_token *start, t_token *end);
void	remove_bracket(t_token **start, t_token **end);

// center.c
t_token	*take_bracket(t_token *curr, t_token *start);
t_token	*get_logical_exp(t_ast *ast, t_token *start, t_token *end);
t_token	*get_pipeline(t_ast *ast, t_token *start, t_token *end);
t_token	*get_center(t_ast *ast, t_token *start, t_token *end);

// check_ast_error.c
void	check_center_error(t_ast *ast, t_token *center);
void	check_redirection_error(t_ast *ast);
int		check_error(t_ast *ast);

// error.c
void	set_parse_error(t_ast *ast, char *string);
void	syntax_error_parser(char *string, t_token **list);

// set_node.c
void	set_start_end(t_ast **ast, t_token *start, t_token *end);

#endif
