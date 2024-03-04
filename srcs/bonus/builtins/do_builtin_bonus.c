/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:22 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:55:04 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "builtin_bonus.h"
#include "env_bonus.h"
#include "execute_bonus.h"

int	do_cd(char **args, t_env_pack *pack)
{
	int		result;
	char	*temp;
	t_env	*target;

	temp = getcwd(0, 0);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (cd_home(pack));
	else if (!ft_strcmp(args[1], "-"))
	{
		target = find_env("OLDPWD", pack);
		if (!target)
		{
			ft_putendl_fd("미니쉘: cd: OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		result = chdir(target->value);
		do_pwd(args, pack);
	}
	else
		result = chdir(args[1]);
	result = check_res(result, pack, temp, args);
	free(temp);
	return (result);
}

int	do_echo(char **args, t_env_pack *pack)
{
	int	i;
	int	n_flag;

	(void)pack;
	i = 1;
	n_flag = 0;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	if (i > 1)
		n_flag = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	do_pwd(char **args, t_env_pack *pack)
{
	char	*cur_path;

	(void)args;
	(void)pack;
	cur_path = getcwd(NULL, 0);
	ft_putendl_fd(cur_path, STDOUT_FILENO);
	free(cur_path);
	return (0);
}

int	do_exit(char **args, t_env_pack *pack)
{
	int	args_len;

	(void)pack;
	args_len = split_len(args);
	if (args_len == 1)
		b_exit(get_exitstat(pack));
	if (args_len == 2)
	{
		if (check_sign(args[1]))
		{
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			b_exit(255);
		}
		else
			b_exit(ft_atoi(args[1]) % 256);
	}
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
	return (1);
}

void	b_exit(int code)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(code);
}
