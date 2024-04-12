/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:19 by yusekim           #+#    #+#             */
/*   Updated: 2024/03/04 15:06:27 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "execute.h"
#include "redirection.h"
#include "expand.h"
#include "env.h"

int	heredoc(t_redir *target, t_env_pack *pack, char *filename)
{
	pid_t			pid;
	int				status;
	struct termios	term;

	set_term(&term);
	signal_ign();
	pid = fork();
	if (pid == -1)
		ft_perror("fork", 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		do_heredoc(target, filename, pack);
	}
	free(target->filename[1]);
	target->filename[1] = filename;
	waitpid(pid, &status, 0);
	reset_term(&term);
	signal_dfl();
	if (WIFSIGNALED(status))
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (1);
	}
	return (0);
}

void	do_heredoc(t_redir *temp, char *f_path, t_env_pack *pack)
{
	int		infile_fd;

	infile_fd = open(f_path, O_WRONLY | O_CREAT, 0644);
	if (infile_fd == -1)
		exit (1);
	write_heredoc(temp, pack, infile_fd);
	free(temp->filename[1]);
	temp->filename[1] = f_path;
	if (close(infile_fd) == -1)
		exit(1);
	exit(0);
}

void	write_heredoc(t_redir *redir, t_env_pack *pack, int inf_fd)
{
	char	*input;
	int		q_flag;
	int		l_len;

	q_flag = heredoc_q_flag(redir->filename[0]);
	l_len = ft_strlen(redir->filename[1]);
	redir->filename[1][l_len] = '\0';
	input = 0;
	while (1)
	{
		if (input)
			heredoc_expander(inf_fd, input, pack, q_flag);
		input = readline(HEREDOC);
		if (!input || !ft_strcmp(input, redir->filename[1]))
			break ;
	}
	if (!input)
		ft_putstr_fd("\e8\e[B\e[A", STDOUT_FILENO);
	free(input);
	redir->filename[1][l_len] = 0;
}

void	heredoc_expander(int fd, char *input, t_env_pack *pack, int flag)
{
	int		i;
	int		j;
	int		exp_len;
	char	*exp_value;

	i = 0;
	while (input[i])
	{
		exp_len = 0;
		j = 0;
		if (input[i] == '$' && flag == 0)
		{
			exp_value = get_heredoc_expval(input + i, pack, &i);
			exp_len = ft_strlen(exp_value);
			while (j < exp_len)
				ft_putchar_fd(*(exp_value + j++), fd);
			free(exp_value);
		}
		else
			write(fd, input + i, 1);
		i++;
	}
	ft_putchar_fd('\n', fd);
	free (input);
}
