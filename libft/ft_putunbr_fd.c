/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:57:35 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/07 16:50:54 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr_fd(unsigned int n, int fd, ssize_t *ret, int *p_ret)
{
	if (n > 9)
		ft_putunbr_fd(n / 10, fd, ret, p_ret);
	if (*ret == -1)
		return ;
	ft_putchar_fd('0' + (n % 10), fd, ret, p_ret);
}
