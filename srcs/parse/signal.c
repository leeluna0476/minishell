/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:19:01 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/23 09:31:47 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "signal_handler.h"
#include <termios.h>

volatile sig_atomic_t	g_status = 0;

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// Ctrl+C -> SIGINT -> prompt
// Ctrl+\ -> SIGQUIT -> nothing
void	sig_handler(int signo)
{
	g_status = signo;
}

int	signal_event(void)
{
	if (g_status == SIGINT)
	{
		// write a newline
		ft_putchar_fd('\n', 1);
		// move the cursor to the newline
		rl_on_new_line();
		// clear the buffer
		rl_replace_line("", 0);
		// redisplay the contents of rl_line_buffer
		rl_redisplay();
		// initialize the signal
		g_status = 0;
	}
	else if (g_status == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		g_status = 0;
	}
	return (0);
}

// rl_event_hook: readline이 terminal input을 기다릴 때 호출되는 함수?
// rl_signal_event_hook: readline이 terminal input을 받다가 interrupt를 받을 때 호출되는 함수?
// rl_on_new_line(); // tell the update funcs that we have moved onto a new empty line.
// rl_redisplay(); // change what's displayed on the screen to reflect the current contents of rl_line_buffer.

// int tcgetattr: shall get the parameters associated with the terminal referred to by fildes and store them in the termios structure referenced by termios_p. The fildes argument is an open file descriptor associated with a terminal.

// int tcsetattr: shall set the parameters associated with the terminal referred to by the open file descriptor fildes (an open file descriptor associated with a terminal) from the termios structure referenced by termios_p.
char	*get_line(char *prompt)
{
	char	*str;

	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
//	rl_signal_event_hook = signal_event;
	str = readline(prompt);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (str);
}
