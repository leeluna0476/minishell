/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:24 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/20 06:55:43 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_structures.h"
#include "builtin.h"
#include "execute.h"

int	is_space(char c);

int	print_export(t_env_pack *pack)
{
	t_env	*temp;

	temp = pack->sorted_head;
	while (temp)
	{
		ft_printf("declare -x %s", temp->name);
		if (temp->value)
			ft_printf("=\"%s\"\n", temp->value);
		else
			ft_printf("\n");
		temp = temp->sorted_next;
	}
	return (0);
}
// 인자가 없는 export를 입력하였을때 bash의 출력에 맞춰 출력해준다.

int	check_env_name(char **args, int i)
{
	int	idx;

	if (ft_isdigit(*args[i]))
	{
		ft_printf("%s: '%s': not a vaild identifier\n", args[0], args[i]);
		return (1);
	}
	idx = 0;
	while (args[i][idx])
	{
		if (!(ft_isalnum(args[i][idx]) || args[i][idx] == '_'))
		{
			ft_printf("%s: '%s': not a vaild identifier\n", args[0], args[i]);
			return (1);
		}
		idx++;
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

int	check_sign(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (1);
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
// 빌트인 exit에서 인자로 들어온 종료코드가 유효한지 체크해주는 함수
// 피신때 atoi와 매우 닮아 있다

void	builtin_fd_set(int *in_fd, int *out_fd, int *std_fd)
{
	*in_fd = 0;
	*out_fd = 1;
	std_fd[0] = 0;
	std_fd[1] = 1;
}
// 나는 놈이 싫다2..

int	is_space(char c)
{
	if (c != '\n' && (c == ' ' || (c >= '\t' && c <= '\r')))
		return (1);
	return (0);
}	// 서진님 코드 훔치기..히히
