/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:39:37 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/01 10:41:49 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include "execute.h"

void	set_exit(t_env_pack *pack, int code)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(code);
	add_env_node(pack, "?", exit_code_str);
	free(exit_code_str);
}

void	ft_perror(const char *str, int exit_num)
{
	ft_putstr_fd("미니쉘: ", STDERR_FILENO);
	ft_putstr_fd((char *)str, STDERR_FILENO);
	if (exit_num == 126)
	{
		if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		else if (errno == EISDIR)
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else if (exit_num == 127)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else if (exit_num == 128)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit_num--;
	}
	else
		perror(" ");
	exit(exit_num);
}
