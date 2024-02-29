/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:24 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 08:03:17 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"
#include "execute.h"

int	check_env_name(char *name)
{
	int	idx;

	if (ft_isdigit(*name))
	{
		ft_putstr_fd("미니쉘: export: '", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	idx = 0;
	while (name && name[idx])
	{
		if (!(ft_isalnum(name[idx]) || name[idx] == '_'))
		{
			ft_putstr_fd("미니쉘: export: '", STDERR_FILENO);
			ft_putstr_fd(name, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		idx++;
	}
	return (0);
}

int	check_res(int res, t_env_pack *pack, char *path, char **args)
{
	char	*str;

	str = getcwd(0, 0);
	if (!res)
	{
		add_env_node(pack, "OLDPWD", path);
		add_env_node(pack, "PWD", str);
		free(str);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		if (!access(args[1], F_OK) && !is_dir(args[1]))
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(str);
		return (1);
	}
}
// chdir함수의 리턴값을 활용하여 cd가 제대로 작동되었는지의 여부를 확인하는 함수
// 또, 정상적으로 작동되었을 경우, 환경변수 "OLDPWD" 와 "PWD"를 업데이트해준다.

int	check_sign(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
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
