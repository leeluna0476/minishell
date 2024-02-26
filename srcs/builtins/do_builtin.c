/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:22 by yusekim           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/22 16:34:22 by yusekim          ###   ########.fr       */
=======
/*   Updated: 2024/02/26 21:43:27 by yusekim          ###   ########.fr       */
>>>>>>> yusekim_test
/*                                                                            */
/* ************************************************************************** */

#include "exec_structures.h"
#include "builtin.h"
#include "env.h"
<<<<<<< HEAD
=======
#include "execute.h"
>>>>>>> yusekim_test

int	do_cd(char **args, t_env_pack *pack)
{
	int		result;
	char	*temp;
	t_env	*target;

	temp = getcwd(0, 0);
	target = find_env("HOME", pack);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)	// "cd" 또는 "cd ~"
		result = chdir(target->value);
	else if (!ft_strcmp(args[1], "-"))				// "cd -" 처리
	{
		target = find_env("OLDPWD", pack);
		if (!target)
		{
<<<<<<< HEAD
			ft_printf("%s: OLDPWD not set\n", args[0]);
=======
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
>>>>>>> yusekim_test
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
// 빌트인 cd 실행시켜주는 함수. '~'와 '-' 도 구현되어있다

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
		ft_printf("%s", args[i]);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
// 옵션 -n이 가능한 echo, "echo -n -n -n -n hello" 등을 처리하기 위해 while문을 활용하였다.

int	do_pwd(char **args, t_env_pack *pack)
{
	char	*cur_path;

	(void)args;
	(void)pack;
	cur_path = getcwd(NULL, 0);
	ft_printf("%s\n", cur_path);
	free(cur_path);
	return (0);
}
// pwd, getcwd함수를 쓰면 바로 가져올 수 있다

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
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			b_exit(255);
		}
		else
			b_exit(ft_atoi(args[1]) % 256);
	}
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	return (1);
}
// exit해주는 함수 bash의 동작과 맞춰주었다..

void	b_exit(int code)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(code);
}
