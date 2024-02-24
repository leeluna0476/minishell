/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:19 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/24 10:15:40 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"
#include "redirection.h"
#include "execute.h"
#include "expand.h"
#include "env.h"

int	heredoc(t_redir *target, t_env_pack *pack)
{
	pid_t	pid;
	int		status;
	char	*filename;

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
	redir->filename[1][l_len] = '\n';
	input = 0;
	while (1)
	{
		if (input)
			heredoc_expander(inf_fd, input, pack, q_flag);
		ft_printf(HEREDOC);
		input = get_next_line(0);
		if (!input || !ft_strncmp(input, redir->filename[1], l_len + 1))
			break ;
	}
	if (!input)
		ft_printf("\n");
	else
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
		if (input[i] == '$' && flag == 0)
		{
			env_name = find_env_name(input + i);
			exp_len = ft_strlen(env_name);
			target = find_env(env_name, pack);
			free(env_name);
			j = 0;
			while (target && target->value && target->value[j])
				write(fd, target->value + j++, 1);
		}
		else
			write(fd, input + i, 1);
		i += exp_len + 1;
	}
	free (input);
}
