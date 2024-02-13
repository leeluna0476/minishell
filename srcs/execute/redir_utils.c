/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:59:01 by yusekim           #+#    #+#             */
/*   Updated: 2024/02/13 14:57:48 by yusekim          ###   ########.fr       */
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
