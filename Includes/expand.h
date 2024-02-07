/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:32:39 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/07 13:31:25 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "structures.h"
# include "utils.h"
# include "env.h"

// expand.c
char	**cmd_expand(char *data, t_env_pack *package);
void	scan_n_setup(t_c_expand *expand, char *data);
void	append_exp_ptr(t_c_expand *expand, t_exp_pair *newpair);
void	delete_quotes(t_c_expand *exp);
void	find_position(t_c_expand *expand);

// cmd_expand.c
void	do_cmd_expand(t_c_expand *expand, t_env_pack *pack);
char	*search_expand(t_exp_pair *pair, t_env_pack *pack);

// expand_utils.c
void	build_exp_pair(t_c_expand *expand);
char	*find_env_name(char *ptr);
char	*appand_string(char *result, char *original, int *start, int end);

#endif
