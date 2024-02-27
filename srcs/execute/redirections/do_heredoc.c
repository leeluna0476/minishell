/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:19 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/27 01:45:36 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "redirection.h"
#include "execute.h"
#include "expand.h"
#include "env.h"

void	set_term(struct termios *term)
{
	tcgetattr(STDIN_FILENO, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void	reset_term(struct termios *term)
{
	term->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

int	heredoc(t_redir *target, t_env_pack *pack)
{
	pid_t			pid;
	int				status;
	char			*filename;
	struct termios	term;

	set_term(&term);
	signal_ign();
	pid = fork();
	filename = get_filename();
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

char	*get_filename(void)
{
	char	*path;
	char	*itoa_out;
	char	*temp_filepath;
	int		num;

	path = getcwd(0, 0);
	temp_filepath = ft_strjoin(path, TEMP_FILENAME);
	free(path);
	path = ft_strdup(temp_filepath);
	num = -1;
	while (!access(path, F_OK))
	{
		free(path);
		itoa_out = ft_itoa(++num);
		path = ft_strjoin(temp_filepath, itoa_out);
		free(itoa_out);
	}
	free(temp_filepath);
	return (path);
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
	// << eof
	// 그냥 마지막 바이트 할당 X.
	redir->filename[1][l_len] = '\0';
	input = 0;
	while (1)
	{
		if (input)
			heredoc_expander(inf_fd, input, pack, q_flag);
//		ft_printf(HEREDOC);
	// readline으로 변경. 제어문자를 입력받지 않기 위해.
		input = readline(HEREDOC);
	// 문자열을 일부가 아닌 전체를 비교해야 해서 strncmp보다는 strcmp가 적절해보였음.
		if (!input || !ft_strcmp(input, redir->filename[1]))
			break ;
	}
	if (!input)
		ft_putstr_fd("\e8\e[B\e[A", STDOUT_FILENO);
//	else
	free(input);
	redir->filename[1][l_len] = 0;
}

void	heredoc_expander(int fd, char *input, t_env_pack *pack, int flag)
{
	int		i;
	int		j;
	int		exp_len;
	char	*env_name;
	t_env	*target;

	i = 0;
	while (input[i])
	{
		exp_len = 0;
		j = 0;
		if (input[i] == '$' && flag == 0)
		{
			env_name = find_env_name(input + i--);
			exp_len = ft_strlen(env_name);
			target = find_env(env_name, pack);
			free(env_name);
			while (target && target->value && target->value[j])
				write(fd, target->value + j++, 1);
		}
		else
			write(fd, input + i, 1);
		i += exp_len + 1;
	}
	write(fd, "\n", 1);
	free (input);
}
