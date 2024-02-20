/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:42:19 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/20 13:16:39 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "expand.h"
#include "env.h"

int	heredoc(t_redir *target, t_env_pack *pack)
{
	char	*filename;
	char	*itoa_out;
	int		num;

	signal(SIGINT, SIG_IGN);
	// signal(SIGINT, handler_heredoc);
	num = -1;
	filename = ft_strdup(TEMP_FILENAME);
	while (!access(filename, F_OK))
	{
		free(filename);
		itoa_out = ft_itoa(++num);
		filename = ft_strjoin(TEMP_FILENAME, itoa_out);
		free(itoa_out);
	}
	return (do_heredoc(target, filename, pack));
}

int	do_heredoc(t_redir *temp, char *f_name, t_env_pack *pack)
{
	int		infile_fd;
	int		temp_exit_status;
	int		fd;

	infile_fd = open(f_name, O_WRONLY | O_CREAT, 0644);
	if (infile_fd == -1)
		exit (1);
	fd = dup(0);
	temp_exit_status = g_exit_status;
	g_exit_status = 0;
	write_heredoc(temp, pack, infile_fd);
	if (g_exit_status)
		dup2(fd, 0);
	// signal(SIGINT, handler);
	free(temp->filename[1]);
	temp->filename[1] = f_name;
	if (close(infile_fd) == -1 || close(fd) == -1)
		exit(1);
	return (detact_exitcode(temp_exit_status));
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
		write(1, "here_doc>", 10);
		input = get_next_line(0);
		if (!input || !ft_strncmp(input, redir->filename[1], l_len + 1))
			break ;
	}
	if (input)
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
		if (input[i] == '$')
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
