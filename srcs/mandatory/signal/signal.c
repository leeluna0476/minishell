/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:19:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/03/04 18:20:50 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "signal_handler.h"
#include "utils.h"

volatile sig_atomic_t	g_status = 0;

void	sig_handler(int signo)
{
	g_status = signo;
}

void	signal_readline(void)
{
	if (g_status == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = -1;
	}
	else if (g_status == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
	}
}

void	signal_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	*get_line(char *prompt, t_env_pack *pack)
{
	char	*str;

	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	str = readline(prompt);
	if (g_status == -1)
	{
		set_exit(pack, 1);
		g_status = 0;
	}
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (str);
}
