/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:28 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/05 15:47:33 by yusekim          ###   ########.fr       */
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
