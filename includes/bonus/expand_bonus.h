/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:32:39 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 16:33:17 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "structures.h"
# include "utils.h"
# include "env.h"
# include "parser.h"

// expand.c
char	**expand(char *data, t_env_pack *package, int flag);
void	scan_n_setup(t_c_expand *expand, char *data);
void	delete_quotes(t_c_expand *exp);
void	find_position(t_c_expand *expand);
void	free_expand(t_c_expand *expand);

// cmd_expand.c
void	do_expand(t_c_expand *expand, t_env_pack *pack);
char	*search_value(t_exp_pair *pair, t_env_pack *pack);
void	expand_add(t_c_expand *expand, char *temp);
void	expand_join(t_c_expand *expand, char *temp);
void	join_remain(t_c_expand *expand, int len);

// expand_utils.c
void	build_exp_pair(t_c_expand *expand, char *ptr, int q_flag);
void	append_exp_ptr(t_c_expand *expand, t_exp_pair *newpair);
char	*find_env_name(char *ptr);
char	*appand_string(char *result, char *original, int *start, int end);
void	add_split(t_c_expand *expand, char **split, int split_len, int idx);

// wildcard.c
int		check_front_center(char *filename, char *pattern, t_mark *mark, int i);
int		check_end(char *filename, char *pattern, t_mark mark, int i);
int		check_wildfixes(char *filename, __uint8_t type, char *pattern);
char	*check_file_access(int idx, char *filename, char *suffix);
char	**expand_wildcard(char *arg);

// wildcard_utils.c
char	*get_tilde_name(t_c_expand *expand, char *ptr);
void	only_wildcard(t_c_expand *expand);
void	do_wildcard(t_c_expand *expand, int i, int bound);
int		scan_for_wildcard(char *str);
char	**insert_strs(char **orig, char **new, int *i);

#endif
