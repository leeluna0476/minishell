/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:59:41 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/13 18:22:25 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd(char c, int fd, ssize_t *ret, int *p_ret)
{
	*ret = write(fd, &c, 1);
	if (*ret != -1)
		(*p_ret)++;
}
