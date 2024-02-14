/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_l_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:29:31 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/08 07:58:04 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_l_fd(unsigned int num, int fd, ssize_t *ret, int *p_ret)
{
	if (num / 16 > 0)
		ft_puthex_l_fd(num / 16, fd, ret, p_ret);
	if (*ret == -1)
		return ;
	ft_putchar_fd("0123456789ABCDEF"[num % 16], fd, ret, p_ret);
}
