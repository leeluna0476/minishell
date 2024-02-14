/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/11 13:07:03 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

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
		if (addr)
			*addr = 0;
		if (check_env_name(args, i))
			continue ;
		if (addr)
		{
			add_env_node(pack, args[i], addr + 1);
			*addr = '=';
		}
		else
			add_env_node(pack, args[i], 0);
	}
	return (1);
}
// 인자가 있는 export 빌트인을 처리하는 함수.
// 모든 인자에 대해 이름 유효성 검사를 진행 후 유효한 이름에 대해 환경변수 구조체 노드를 만들어 준다.

int	do_unset(char **args, t_env_pack *pack)
{
	int		i;

	g_exit_status = 0;
	i = 0;
	while (args[++i])
	{
		if (check_env_name(args, i))
			continue ;
		delete_env(args[i], pack);
	}
	return (1);
}
// unset구현함수, 이름 유효성 검사를 먼저 한 뒤 유효한 이름일시 환경변수 구조체에서 지워준다.
// 하하 전위연산자가 필요합니당!

int	do_env(char **args, t_env_pack *pack)
{
	t_env	*temp;

	if (split_len(args) > 1)
	{
		ft_printf("%s: %s: No such file or directory\n");
		g_exit_status = 127;
		return (1);
	}
	g_exit_status = 0;
	temp = pack->origin_head;
	while (temp)
	{
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->origin_next;
	}
	return (1);
}
// env구현함수, bash에 출력에 맞게 출력해주면 된다.

int	do_exit(char **args, t_env_pack *pack)
{
	int		args_len;

	args_len = split_len(args);
	g_exit_status = 0;
	if (args_len > 2)
	{
		ft_printf("%s: too many arguments\n", args[0]);
		g_exit_status = 1;
		return (1);
	}
	if (args_len == 2)
	{
		if (check_sign(args[1]))
		{
			ft_printf("%s: %s: numeric argument required\n", args[0], args[1]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
		else
			g_exit_status = ft_atoi(args[1]) % 256;
	}
	exit(g_exit_status);
}
// exit해주는 함수 bash의 동작과 맞춰주었다..
