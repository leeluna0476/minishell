/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:08:05 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 18:55:04 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures_bonus.h"
#include "builtin_bonus.h"

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
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			res = 1;
			continue ;
		}
		check_n_add(pack, args[i], addr, &res);
	}
	return (res);
}

int	print_export(t_env_pack *pack)
{
	t_env	*temp;

	temp = pack->sorted_head->sorted_next;
	while (temp)
	{
		// if (ft_strncmp(temp->name, "~", 2) == 0)
		// 	temp = temp->sorted_next;
		ft_printf("%s", temp->name);
		if (temp->value)
			ft_printf("=\"%s\"\n", temp->value);
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
		temp = temp->sorted_next;
	}
	return (0);
}

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

int	do_env(char **args, t_env_pack *pack)
{
	t_env	*temp;

	(void)args;
	temp = pack->origin_head->origin_next->origin_next;
	while (temp)
	{
		if (temp->value)
			ft_printf("%s=%s\n", temp->name, temp->value);
		temp = temp->origin_next;
	}
	return (0);
}
