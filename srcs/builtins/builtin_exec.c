/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:28 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/02 15:18:05 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

enum e_builtin_type	check_is_builtin(char *arg)
{
	if (ft_strcmp("echo", arg) == 0)
		return (B_ECHO);
	else if (ft_strcmp("cd", arg) == 0)
		return (B_CD);
	else if (ft_strcmp("pwd", arg) == 0)
		return (B_PWD);
	else if (ft_strcmp("export", arg) == 0)
		return (B_EXPORT);
	else if (ft_strcmp("unset", arg) == 0)
		return (B_UNSET);
	else if (ft_strcmp("env", arg) == 0)
		return (B_ENV);
	else if (ft_strcmp("exit", arg) == 0)
		return (B_EXIT);
	else
		return (B_FALSE);
}

int	exec_builtin(char **args, t_env_pack *pack)
{
	int					i;
	const t_builtin_ptr	f_ptr_list[] = \
	{do_echo, do_cd, do_pwd, do_export, do_unset, do_env, do_exit};

	i = check_is_builtin(*args);
	if (i == -1)
	{
		ft_printf("not a builtin\n");
		return (0);
	}
	else
		return (f_ptr_list[i](args, pack));
}

int	do_cd(char **args, t_env_pack *pack)
{
	ft_printf("cd\n");
	return (1);
}

int	do_echo(char **args, t_env_pack *pack)
{
	ft_printf("echo\n");
	return (1);
}

int	do_pwd(char **args, t_env_pack *pack)
{
	ft_printf("pwd\n");
	return (1);
}

int	do_export(char **args, t_env_pack *pack)
{
	ft_printf("export\n");
	return (1);
}

int	do_unset(char **args, t_env_pack *pack)
{
	ft_printf("unset\n");
	return (1);
}

int	do_env(char **args, t_env_pack *pack)
{
	ft_printf("env\n");
	return (1);
}

int	do_exit(char **args, t_env_pack *pack)
{
	ft_printf("exit\n");
	return (1);
}

