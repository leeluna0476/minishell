/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:13:02 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/02 22:52:33 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "./srcs/libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_env_pack	package;
	t_env		*temp;

	build_envp(&package, envp);
	// temp = package.origin_head;
	// ft_printf("\n===================================================================================\n");
	// ft_printf("                                   Printing envs\n");
	// ft_printf("======================================================================================\n\n");
	// while (temp)
	// {
	// 	ft_printf("%s=", temp->name);
	// 	ft_printf("%s\n", temp->value);
	// 	temp = temp->origin_next;
	// }

	ft_printf("\n\n\n===================================================================================\n");
	ft_printf("                               Printing envs in order\n");
	ft_printf("===================================================================================\n\n");
	temp = package.sorted_head;
	while (temp)
	{
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->sorted_next;
	}


	ft_printf("\n\n\n===================================================================================\n");
	ft_printf("                                   Builtin check\n");
	ft_printf("===================================================================================\n\n");
	exec_builtin(++argv, &package);

	temp = package.origin_head;
	ft_printf("\n===================================================================================\n");
	ft_printf("                                   Printing envs\n");
	ft_printf("======================================================================================\n\n");
	while (temp)
	{
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->origin_next;
	}

	return (0);
}
