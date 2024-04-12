/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:47:35 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/05 09:24:54 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "structures.h"

// build_env_pack.c
void	set_shlvl(t_env_pack *pack);
void	set_tilde(t_env_pack *pack);
void	build_envp(t_env_pack *pack, char **envp);
void	add_env_node(t_env_pack *pack, char *name, char *value);
void	add_sorted_node(t_env **sorted_head, t_env *new);

// env_util.c
void	set_new_env(t_env_pack *pack, t_env *new);
t_env	*find_env(char *name, t_env_pack *package);
void	delete_env(char *name, t_env_pack *package);
void	free_envs(t_env *head);
char	*get_home_dir(void);

#endif
