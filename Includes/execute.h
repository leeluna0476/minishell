/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:39:36 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 10:00:51 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "structures.h"
# include "utils.h"

// execute.c
void	do_execution(t_ast *tree, t_env_pack *pack, int level);
void	build_cmd_pack(t_ast *tree, t_env_pack *pack, t_cmd *cmd);

#endif
