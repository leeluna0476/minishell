/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:28 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/03 16:31:52 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

enum e_b_type	check_is_builtin(char *arg)
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
// 열거형 builtin_type 을 리턴해주는 함수. ft_strcmp를 활용하였다.

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
// 함수 포인터 배열을 사용하여 check_is_builtin의 리턴값에 맞는 함수를 실행시켜준다

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
			ft_printf("%s: OLDPWD not set\n", args[0]);
			g_exit_status = 1;
			return (1);
		}
		result = chdir(target->value);
		do_pwd(args, pack);
	}
	else
		result = chdir(args[1]);
	check_result(result, pack, temp, args);
	return (1);
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
		ft_printf("%s", args[i++]);
	if (!n_flag)
		ft_printf("\n");
	g_exit_status = 0;
	return (1);
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
	g_exit_status = 0;
	return (1);
}
// pwd, getcwd함수를 쓰면 바로 가져올 수 있다

int	do_export(char **args, t_env_pack *pack)
{
	int		i;
	char	*addr;

	g_exit_status = 0;
	if (split_len(args) == 1)
		return (print_export(pack));
	i = 0;
	while (args[++i])
	{
		addr = ft_strchr(args[i], '=');
		*addr = 0;
		if (check_env_name(args[i]))
		{
			ft_printf("not a valid identifier");
			g_exit_status = 1;
			*addr = '=';
			continue ;
		}
		else
			add_env_node(pack, args[i], addr + 1);
			*addr = '=';
	}
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

