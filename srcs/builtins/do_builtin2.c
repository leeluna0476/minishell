/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/22 17:53:06 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_structures.h"
#include "builtin.h"

int	do_export(char **args, t_env_pack *pack)
{
	int		idx_n_res[2];
	char	*addr;

	if (split_len(args) == 1)
		return (print_export(pack));
	idx_n_res[0] = 0;
	idx_n_res[1] = 0;
	while (args[++idx_n_res[0]])
	{
		addr = ft_strchr(args[idx_n_res[0]], '=');
		if (addr)
		{
			*addr = 0;
			if (check_env_name(args, idx_n_res[0]))
			{
				idx_n_res[1] = 1;
				continue ;
			}
			add_env_node(pack, args[idx_n_res[0]], addr + 1);
			*addr = '=';
		}
		else
		{
			if (check_env_name(args, idx_n_res[0]))
			{
				idx_n_res[1] = 1;
				continue ;
			}
			add_env_node(pack, args[idx_n_res[0]], 0);
		}
	}
	return (idx_n_res[1]);
}
// 인자가 있는 export 빌트인을 처리하는 함수.
// 모든 인자에 대해 이름 유효성 검사를 진행 후 유효한 이름에 대해 환경변수 구조체 노드를 만들어 준다.
// 진짜 놈 개싫다 ㄹㅇ..진짜 화나네 이거 아니 내가 밤새면서 이렇게까지 해야해? 진짜 줄 한줄때문에 int배열 2칸짜리만든거 정말 맘에 안드네 >:(

int	do_unset(char **args, t_env_pack *pack)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (check_env_name(args, i))
			continue ;
		delete_env(args[i], pack);
	}
	return (0);
}
// unset구현함수, 이름 유효성 검사를 먼저 한 뒤 유효한 이름일시 환경변수 구조체에서 지워준다.
// 하하 전위연산자가 필요합니당!

int	do_env(char **args, t_env_pack *pack)
{
	t_env	*temp;

	if (split_len(args) > 1)
	{
		ft_printf("%s: %s: No such file or directory\n");
		return (127);
	}
	temp = pack->origin_head->origin_next;
	while (temp)
	{
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->origin_next;
	}
	return (0);
}
// env구현함수, bash에 출력에 맞게 출력해주면 된다.

int	do_exit(char **args, t_env_pack *pack)
{
	int	args_len;

	(void)pack;
	args_len = split_len(args);
	// 그냥 exit도 exit이 되도록. 검수 필요.
	if (args_len <= 2)
	{
		if (check_sign(args[1]))
		{
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			B_EXIT(255);
		}
		else
			B_EXIT(ft_atoi(args[1]) % 256);
	}
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	return (1);
}
// exit해주는 함수 bash의 동작과 맞춰주었다..
