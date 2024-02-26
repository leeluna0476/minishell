/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:03:00 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/20 13:38:23 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../srcs/libft/libft.h"
# include "parse_define.h"
# include "parse_struct.h"

// error.c
void	syntax_error_tokenizer(char *string, t_token **list);

// get_token.c
int		get_meta1(char *line, char **string, t_type *type);
int		get_quote(char *line, int *flag, int *idx);
int		get_meta2(char *line, char **string, t_type *type);

// meta.c
int		is_meta1(char c);
int		is_meta2(char c);
void	set_type_meta1(char c, int i, t_type *type);

// token_utils.c
t_token	*new_token(char *string, t_type type);
t_token	*last_token(t_token *list);
void	add_token(t_token **list, t_token *token);
void	free_token(t_token **token);
void	free_tokens(t_token **tokens);

// tokenizer.c
t_type	get_type(char *string, int i);
int		remove_space(char *line);
int		get_word(char *line, char **string, t_type *type);
void	update_list(t_token **list, char *string, t_type type);
t_token	*tokenizer(char *line);

#endif
