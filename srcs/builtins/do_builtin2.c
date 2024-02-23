/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/23 10:54:12 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_structures.h"
#include "builtin.h"

int	do_export(char **args, t_env_pack *pack)
{
	int		idx;
	int		result;
	char	*name;

	if (split_len(args) == 1)
		return (print_export(pack));
	idx = 0;
	result = 0;
	while (args[++idx])
	{
		name = get_env_name(args[idx]);
		if (check_env_name(name))
			result = 1;
		add_env_node(pack, name, 0);
		free(name);
	}
	return (result);
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

int	do_unset(char **args, t_env_pack *pack)
{
	int		i;
	char	*name;

	i = 0;
	while (args[++i])
	{
		name = get_env_name(args[i]);
		if (check_env_name(name))
		{
			free(name);
			continue ;
		}
		delete_env(name, pack);
		free(name);
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
