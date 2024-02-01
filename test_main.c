/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:13:02 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/01 17:37:43 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "./srcs/libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_env_pack	package;
	t_env		*temp;
	int			count;

	(void)argv;
	if (argc != 1)
		return (1);

	build_envp(&package, envp);
	temp = package.origin_head;
	ft_printf("\n==========================================================\n");
	ft_printf("                     Printing envs\n");
	ft_printf("==========================================================\n\n");
	count = 0;
	while (temp)
	{
		count++;
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->origin_next;
	}
	ft_printf("count: %d\n", count);

	count = 0;
	ft_printf("\n\n\n==========================================================\n");
	ft_printf("                     Printing envs in order\n");
	ft_printf("==========================================================\n\n");
	temp = package.sorted_head;
	while (temp)
	{
		count++;
		ft_printf("%s=", temp->name);
		ft_printf("%s\n", temp->value);
		temp = temp->sorted_next;
	}
	ft_printf("count: %d\n", count);

	return (0);
}
