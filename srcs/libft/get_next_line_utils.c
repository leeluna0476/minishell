/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:42:37 by youwin0802        #+#    #+#             */
/*   Updated: 2024/02/14 10:05:04 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strnlen(char *str, int type)
{
	int	idx;

	idx = 0;
	if (!str)
		return (idx);
	if (type == 0)
	{
		while (str[idx])
			idx++;
	}
	else
	{
		while (str[idx])
		{
			if (str[idx] == '\n')
				return (idx + 1);
			idx++;
		}
	}
	return (idx);
}

void	*gnl_memcpy(void *dst, void *src, int n)
{
	unsigned char	*c_dst;
	unsigned char	*c_src;

	if (n <= 0)
		return (0);
	if (dst == src)
		return (dst);
	c_dst = (unsigned char *)dst;
	c_src = (unsigned char *)src;
	while (n-- > 0)
		*c_dst++ = *c_src++;
	return (dst);
}
