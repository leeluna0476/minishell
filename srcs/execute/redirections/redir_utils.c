/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:01 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/19 13:25:37 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "expand.h"

void	redir_open(t_redir *temp)
{
	if (temp->type == T_LESSER)
		temp->fd = open(temp->filename[1], O_RDONLY);
	else if (temp->type == T_GREATER)
		temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (temp->type == T_D_GREATER)
		temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

char	*trim_quotes(char *data)
{
	char	*out;
	int		idx;
	int		flag;
	int		start_pos;

	out = 0;
	idx = -1;
	flag = 0;
	start_pos = 0;
	while (data[++idx])
	{
		if (!flag && (data[idx] == '\'' || data[idx] == '"'))
		{
			out = appand_string(out, data, &start_pos, idx);
			flag = data[idx];
		}
		else if (flag && flag == data[idx])
		{
			out = appand_string(out, data, &start_pos, idx);
			flag = 0;
		}
	}
	out = appand_string(out, data, &start_pos, idx);
	return (out);
}

int	heredoc_q_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	detact_exitcode(int temp)
{
	if (g_exit_status)
	{
		g_exit_status = temp;
		return (1);
	}
	else
	{
		g_exit_status = temp;
		return (0);
	}
}

char	*itoa(int n)
{
	int		size;
	int		temp;
	char	*out;

	if (n == 0)
		return (ft_strdup("0"));
	size = 0;
	temp = n;
	while (temp)
	{
		temp /= 10;
		size++;
	}
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		exit(1);
	out[size] = '\0';
	while (n)
	{
		out[--size] = (n % 10) + '0';
		n /= 10;
	}
	return (out);
}
