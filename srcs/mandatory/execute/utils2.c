/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:39:37 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 13:55:33 by seojilee         ###   ########.fr       */
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
			ft_putendl_fd(": Not a directory", STDERR_FILENO);
		else if (errno == EISDIR)
			ft_putendl_fd(": is a directory", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else if (exit_num == 127)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (exit_num == 128)
	{
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		exit_num--;
	}
	else
		perror(" ");
	exit(exit_num);
}
