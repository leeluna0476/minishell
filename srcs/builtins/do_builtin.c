/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:22 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 11:08:38 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/structures.h"
#include "../../Includes/builtin.h"

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
	check_res(result, pack, temp, args);
	return (1);
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
		ft_printf("%s ", args[i]);
		i++;
	}
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
