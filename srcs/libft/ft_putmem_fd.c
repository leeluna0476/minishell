/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:46:35 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/07 18:46:37 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putmem_fd(unsigned long long num, int fd, ssize_t *ret, int *p_ret)
{
	if (num / 16 > 0)
		ft_putmem_fd(num / 16, fd, ret, p_ret);
	else if (num / 16 <= 0)
	{
		*ret = write(fd, "0x", 2);
		*p_ret += 2;
	}
	if (*ret == -1)
		return ;
	ft_putchar_fd("0123456789abcdef"[num % 16], fd, ret, p_ret);
}
