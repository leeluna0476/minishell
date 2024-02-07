/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/05 15:30:08 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "builtin.h"

int	do_export(char **args, t_env_pack *pack)
{
	int		i;
	char	*addr;

	g_exit_status = 0;
	if (split_len(args) == 1)
		return (print_export(pack));
	i = 0;
	while (args[++i])
	{
		addr = ft_strchr(args[i], '=');
		if (addr)
			*addr = 0;
		if (check_env_name(args, i))
			continue ;
		if (addr)
		{
			add_env_node(pack, args[i], addr + 1);
			*addr = '=';
		}
		else
			add_env_node(pack, args[i], 0);
	}
	return (1);
}

int	do_unset(char **args, t_env_pack *pack)
{
	int		i;

	g_exit_status = 0;
	i = 0;
	while (args[++i])
	{
		if (check_env_name(args, i))
			continue ;
		delete_env(args[i], pack);
	}
	return (1);
}
// 하하 전위연산자가 필요합니당!

int	do_env(char **args, t_env_pack *pack)
{
	t_env	*temp;

	if (split_len(args) > 1)
	{
		ft_printf("%s: %s: No such file or directory\n");
		g_exit_status = 127;
		return (1);
	}
	g_exit_status = 0;
	temp = pack->origin_head;
	while (temp)
	{
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->origin_next;
	}
	return (1);
}

int	do_exit(char **args, t_env_pack *pack)
{
	ft_printf("exit\n");
	return (1);
}
