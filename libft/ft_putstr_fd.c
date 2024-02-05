/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:00:42 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/08 08:02:15 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_fd(char *s, int fd, ssize_t *ret, int *p_ret)
{
	size_t	i;

	if (!s)
	{
		*ret = write(1, "(null)", 6);
		if (*ret == -1)
			return ;
		*p_ret += 6;
		return ;
	}
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd, ret, p_ret);
		if (*ret == -1)
			return ;
		i++;
	}
}
