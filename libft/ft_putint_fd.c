/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:57:29 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/07 17:06:55 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putint_fd(int n, int fd, ssize_t *ret, int *p_ret)
{
	if (n == ((int)1 << (sizeof(int) * 8 - 1)))
	{
		ft_putint_fd(n / 10, fd, ret, p_ret);
		if (*ret == -1)
			return ;
		ft_putchar_fd('0' + 8, fd, ret, p_ret);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd, ret, p_ret);
		if (*ret == -1)
			return ;
		ft_putint_fd(-n, fd, ret, p_ret);
	}
	else
	{
		if (n > 9)
			ft_putint_fd(n / 10, fd, ret, p_ret);
		if (*ret == -1)
			return ;
		ft_putchar_fd('0' + (n % 10), fd, ret, p_ret);
	}
}
