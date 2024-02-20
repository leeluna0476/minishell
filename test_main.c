/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:13:02 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/20 04:59:21 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "./srcs/libft/libft.h"
#include "expand.h"

void	leaks()
{
	system("leaks minishell");
}

void	set_info(t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->pipe_fds[1] = 1;
	info->redir_fds[1] = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_env_pack	package;
	char		**expand_out;
	t_info		info;

	build_envp(&package, envp);
	// if (argc > 1)
		// exec_builtin(++argv, &package);
	// char *quote = ft_strdup("'$single' \"$double\" $1invaild@ \'$muyahoo\'");
	// char *quote = ft_strdup("Hello\"\" \'this is a str\"ing for quote\' t\'es   \'t");
	// char *quote = ft_strdup("echo \"\"$PWD\"\"qwere\"qwqwer$P$P$PWD\"\'$PWD\'\"\"");
	char *quote = ft_strdup("< a echo > b");
	// char *quote = ft_strdup("ABC\'$USER$a\'$a\"\"1\'$HOME\'12$LESS 123"); // ABC$USER""1'$HOME'12$LESS 123

	ft_printf("original: [%s]\n", quote);
	expand_out = expand(quote, &package, 0);
	free_envs(package.origin_head);
	split_free(expand_out);
	set_info(&info);
	// atexit(leaks);
}			// 확장 테스트용 코드
