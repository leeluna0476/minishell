/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:38:38 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/02 15:09:10 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "structures.h"
# include "utils.h"
# include "env.h"

enum	e_builtin_type
{
	B_FALSE = -1,
	B_ECHO,
	B_CD,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
};

typedef int	(*t_builtin_ptr)(char **, t_env_pack *);

int					exec_builtin(char **args, t_env_pack *pack);
enum e_builtin_type	check_is_builtin(char *arg);
int					do_echo(char **args, t_env_pack *pack);
int					do_cd(char **args, t_env_pack *pack);
int					do_pwd(char **args, t_env_pack *pack);
int					do_export(char **args, t_env_pack *pack);
// int					print_export(t_env_pack *pack);
// int					add_export(char **args, t_env_pack *pack);
int					do_unset(char **args, t_env_pack *pack);
int					do_env(char **args, t_env_pack *pack);
int					do_exit(char **args, t_env_pack *pack);

#endif
