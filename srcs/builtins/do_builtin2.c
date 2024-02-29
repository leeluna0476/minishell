/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 08:03:17 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

int	do_export(char **args, t_env_pack *pack)
{
	int		i;
	int		res;
	char	*addr;

	if (split_len(args) == 1)
		return (print_export(pack));
	i = 0;
	res = 0;
	while (args[++i])
	{
		addr = ft_strchr(args[i], '=');
		if (addr == args[i])
		{
			ft_putstr_fd("미니쉘: export: '", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			res = 1;
			continue ;
		}
		check_n_add(pack, args[i], addr, &res);
	}
	return (res);
}
// 인자가 있는 export 빌트인을 처리하는 함수.
// 모든 인자에 대해 이름 유효성 검사를 진행 후 유효한 이름에 대해 환경변수 구조체 노드를 만들어 준다.
// 진짜 놈 개싫다 ㄹㅇ..진짜 화나네 이거 아니 내가 밤새면서 이렇게까지 해야해? 진짜 줄 한줄때문에 int배열 2칸짜리만든거 정말 맘에 안드네 >:(

int	print_export(t_env_pack *pack)
{
	t_env	*temp;

	temp = pack->sorted_head->sorted_next;
	while (temp)
	{
		ft_printf("%s", temp->name);
		if (temp->value)
			ft_printf("=\"%s\"\n", temp->value);
		else
			ft_printf("\n");
		temp = temp->sorted_next;
	}
	return (0);
}
// 인자가 없는 export를 입력하였을때 bash의 출력에 맞춰 출력해준다.

void	check_n_add(t_env_pack *pack, char *arg, char *ptr, int *res)
{
	if (!ptr)
	{
		if (check_env_name(arg))
			*res = 1;
		else
			add_env_node(pack, arg, 0);
	}
	else
	{
		*ptr = 0;
		if (check_env_name(arg))
			*res = 1;
		else
			add_env_node(pack, arg, ptr + 1);
		*ptr = '=';
	}
}

int	do_unset(char **args, t_env_pack *pack)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (check_env_name(args[i]))
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

	(void)args;
	temp = pack->origin_head->origin_next;
	while (temp)
	{
		if (temp->value)
			ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->origin_next;
	}
	return (0);
}
// env구현함수, bash에 출력에 맞게 출력해주면 된다.
