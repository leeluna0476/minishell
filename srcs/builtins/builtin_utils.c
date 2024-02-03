/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:24 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/03 16:34:18 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

int	print_export(t_env_pack *pack)
{
	t_env	*temp;

	temp = pack->sorted_head;
	while (temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		temp = temp->sorted_next;
	}
	return (1);
}

int	check_env_name(char *name)
{
	int	i;

	if (ft_isdigit(*name))
		return (1);
	i = 0;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}
// 환경변수 이름 생성시의 규칙을 체크하는 함수
// 환경변수명이 숫자로 시작하지 않아야하고, 알파벳, 숫자, 그리고 '_'문자만이 이름에 포함될 수 있다.

void	check_res(int res, t_env_pack *pack, char *path, char **args)
{
	if (!res)
	{
		add_env_node(pack, "OLDPWD", path);
		free(path);
		add_env_node(pack, "PWD", getcwd(0, 0));
		g_exit_status = 0;
	}
	else
	{
		ft_printf("%s: %s: No such file or directory\n", args[0], args[1]);
		g_exit_status = 1;
	}
}
// chdir함수의 리턴값을 활용하여 cd가 제대로 작동되었는지의 여부를 확인하는 함수
// 또, 정상적으로 작동되었을 경우, 환경변수 "OLDPWD" 와 "PWD"를 업데이트해준다.
