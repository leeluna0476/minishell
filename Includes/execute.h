/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youwin0802 <youwin0802@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:36 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/15 14:58:07 by youwin0802       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "structures.h"
# include "utils.h"

// execute.c
void	do_execution(t_ast *tree, t_env_pack *pack, int level, int *fds);
t_cmd	*build_cmd_pack(t_ast *tree, t_env_pack *pack);
void	execute(t_ast *tree, t_env_pack *pack, int level, int *fds);

// execute_utils.c
void	set_fd(t_cmd *cur, int *fds, int *tmp_fds);
char	**make_envp(t_env_pack *envs);
int		is_route(char *str);
int		is_dir(char *str);

#endif
