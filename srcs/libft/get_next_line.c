/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:42:42 by youwin0802        #+#    #+#             */
/*   Updated: 2024/02/14 10:05:23 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_remain(char *remain, char **newline)
{
	int		nl_idx;
	int		t_len;

	nl_idx = gnl_strnlen(remain, 1);
	t_len = gnl_strnlen(remain, 0);
	if (!t_len || (nl_idx == t_len && remain[t_len - 1] != '\n'))
	{
		if (t_len)
		{
			*newline = malloc(sizeof(char) * (t_len + 1));
			if (!*newline)
				return (-1);
			gnl_memcpy(*newline, remain, t_len + 1);
		}
		return (1);
	}
	else
	{
		*newline = malloc(sizeof(char) * (nl_idx + 1));
		if (!*newline)
			return (-1);
		(*newline)[nl_idx] = '\0';
		gnl_memcpy(*newline, remain, nl_idx);
		return (0);
	}
}

char	*build_remain(char *remain, char *str, int *ret)
{
	char	*new_rem;
	int		t_len;
	int		nl_idx;

	new_rem = 0;
	t_len = gnl_strnlen(str, 0);
	nl_idx = gnl_strnlen(str, 1);
	if (t_len != nl_idx)
	{
		new_rem = malloc(sizeof(char) * (t_len - nl_idx + 1));
		if (!new_rem)
		{
			*ret = -1;
			free(remain);
			return (NULL);
		}
		new_rem[t_len - nl_idx] = '\0';
		gnl_memcpy(new_rem, str + nl_idx, t_len - nl_idx);
	}
	free(remain);
	return (new_rem);
}

char	*buf_check_n_join(char *newline, char *buf, int *ret)
{
	char	*updated_line;
	int		t_len;
	int		nl_idx;

	if (*ret == 0)
		return (newline);
	t_len = gnl_strnlen(newline, 0);
	nl_idx = gnl_strnlen(buf, 1);
	if (*ret == nl_idx && buf[nl_idx - 1] != '\n')
		*ret = 1;
	else
		*ret = 0;
	updated_line = malloc(sizeof(char) * (t_len + nl_idx + 1));
	if (!updated_line)
	{
		*ret = -1;
		return (newline);
	}
	updated_line[t_len + nl_idx] = '\0';
	gnl_memcpy(updated_line, newline, t_len);
	gnl_memcpy(updated_line + t_len, buf, nl_idx);
	free(newline);
	return (updated_line);
}

void	*free_all(char **remain, char *newline)
{
	if (*remain)
		free(*remain);
	*remain = 0;
	if (newline)
		free(newline);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*newline;
	int			ret;
	char		buf[BUFFER_SIZE + 1];

	newline = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = check_remain(remain, &newline);
	if (ret == 0)
		remain = build_remain(remain, remain, &ret);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			break ;
		buf[ret] = '\0';
		newline = buf_check_n_join(newline, buf, &ret);
		if (ret == 0)
			remain = build_remain(remain, buf, &ret);
	}
	if (ret == -1)
		return (free_all(&remain, newline));
	return (newline);
}
