/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:40:06 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/07 16:31:10 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_variable	var;

	va_start(ap, format);
	var.i = 0;
	var.ret = 0;
	var.p_ret = 0;
	while (format[var.i])
	{
		if (var.ret == -1)
			return (var.ret);
		if (format[var.i] == '%')
		{
			var.i++;
			ft_puts(format[var.i], ap, &var);
			var.i++;
		}
		else
			ft_putchar_fd(format[var.i++], 1, &var.ret, &var.p_ret);
	}
	if (var.i == 0)
		ft_putchar_fd(format[var.i], 1, &var.ret, &var.p_ret);
	va_end(ap);
	return (var.p_ret);
}
