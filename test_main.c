/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:13:02 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/08 17:58:28 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "./srcs/libft/libft.h"
#include "expand.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env_pack	package;
// 	t_env		*temp;

// 	build_envp(&package, envp);
// 	// temp = package.origin_head;
// 	// ft_printf("\n===================================================================================\n");
// 	// ft_printf("                                   Printing envs\n");
// 	// ft_printf("======================================================================================\n\n");
// 	// while (temp)
// 	// {
// 	// 	ft_printf("%s=", temp->name);
// 	// 	ft_printf("%s\n", temp->value);
// 	// 	temp = temp->origin_next;
// 	// }

// 	// ft_printf("\n\n\n===================================================================================\n");
// 	// ft_printf("                               Printing envs in order\n");
// 	// ft_printf("===================================================================================\n\n");
// 	// temp = package.sorted_head;
// 	// while (temp)
// 	// {
// 	// 	ft_printf("%s=", temp->name);
// 	// 	ft_printf("%s\n", temp->value);
// 	// 	temp = temp->sorted_next;
// 	// }


// 	if (argc > 1)
// 	{
// 		ft_printf("\n\n\n===================================================================================\n");
// 		ft_printf("                                   Builtin check\n");
// 		ft_printf("===================================================================================\n\n");
// 		exec_builtin(++argv, &package);
// 	}

// 	ft_printf("\n\n\n===================================================================================\n");
// 	ft_printf("                               Printing envs in order\n");
// 	ft_printf("===================================================================================\n\n");
// 	print_export(&package);

// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env_pack	package;

	build_envp(&package, envp);
	if (argc > 1)
		exec_builtin(++argv, &package);
	// char *expandstr = ft_strdup("'$single' \"$double\" $1invaild@ \'$muyahoo\'");
	// char *expandstr = ft_strdup("hello '$sing' \"$double\" $1invaild@ \'$muyahoo\'");
	// char *quote = ft_strdup("Hello\"\" \'this is a str\"ing for quote\' t\'es   \'t");
	// char *quote = ft_strdup("echo $a\"\"$PWD\"\"qwere\"qwqwer$P$P$PWD\"\'$PWD\'\"\"");
	char *quote = ft_strdup("$a\"\"hello");
	// char *quote = ft_strdup("ABC$USER\"\"1\'$HOME\'12$LESS 123"); // ABC$USER""1'$HOME'12$LESS 123

	ft_printf("original: [%s]\n", quote);
	expand(quote, &package);
}			// 확장 테스트용 코드
