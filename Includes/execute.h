/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:36 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 11:01:33 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "exec_structures.h"
# include "utils.h"

// execute.c
void	do_execution(t_ast *tree, t_env_pack *pack, t_info *info);
t_cmd	*build_cmd_pack(t_ast *tree, t_env_pack *pack);
void	execute(t_ast *tree, t_env_pack *pack, t_info *info);

// execute_utils.c
void	set_fd(t_cmd *cur, t_info *info);
char	**make_envp(t_env_pack *envs);
int		is_route(char *str);
int		is_dir(char *str);

#endif
