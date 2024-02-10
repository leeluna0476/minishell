/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:35 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/10 16:53:50 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "structures.h"

// build_env_pack.c
void	build_envp(t_env_pack *pack, char **envp);
void	add_env_node(t_env_pack *pack, char *name, char *value);
void	set_new_env(t_env_pack *pack, t_env *new);
void	add_sorted_node(t_env **sorted_head, t_env *new);

// env_util.c
t_env	*find_env(char *name, t_env_pack *package);
void	delete_env(char *name, t_env_pack *package);
void	free_envs(t_env *head);

#endif
