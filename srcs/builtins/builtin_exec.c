/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:28 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/14 09:41:32 by yusekim          ###   ########.fr       */
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
		return (0);
	else
		return (f_ptr_list[i](args, pack));
}
// 함수 포인터 배열을 사용하여 check_is_builtin의 리턴값에 맞는 함수를 실행시켜준다

int	solo_builtin(t_cmd *cur, t_env_pack *pack)
{
	int	std_fd[2];
	int	in_fd;
	int	out_fd;
	int	res;

	res = 0;
	builtin_fd_set(&in_fd, &out_fd, std_fd);
	b_check_redir(cur, std_fd, &in_fd, &out_fd);
	if (in_fd != 0)
		close(in_fd);
	if (out_fd != 1)
		close(out_fd);
	if (exec_builtin(cur->c_args, pack))
		res = 1;
	if (cur->in_redirs)
	{
		dup2(std_fd[0], 0);
		close(std_fd[0]);
	}
	if (cur->out_redirs)
	{
		dup2(std_fd[1], 1);
		close(std_fd[1]);
	}
	return (res);
}
// input 값이 단일 builtin일 경우, 리다이렉션 연결 후 바로 실행해준다.

void	b_check_redir(t_cmd *cur, int *std_fd, int *in_fd, int *out_fd)
{
	if (cur->in_redirs)
	{
		std_fd[0] = dup(0);
		*in_fd = open(cur->in_redirs->filename[1], O_RDONLY);
		dup2(*in_fd, 0);
	}
	if (cur->out_redirs)
	{
		std_fd[1] = dup(1);
		if (cur->out_redirs->type == T_D_GREATER)
			*out_fd = open(cur->out_redirs->filename[1],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			*out_fd = open(cur->out_redirs->filename[1],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(*out_fd, 1);
	}
}
