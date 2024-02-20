/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:43:55 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/08 07:57:51 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puts(char form, va_list ap, t_variable *var)
{
	if (form == 'c')
		ft_putchar_fd(va_arg(ap, int), 1, &var->ret, &var->p_ret);
	else if (form == 's')
		ft_putstr_fd(va_arg(ap, char *), 1, &var->ret, &var->p_ret);
	else if (form == 'i' || form == 'd')
		ft_putint_fd(va_arg(ap, int), 1, &var->ret, &var->p_ret);
	else if (form == 'u')
		ft_putunbr_fd(va_arg(ap, unsigned int), 1, &var->ret, &var->p_ret);
	else if (form == 'x')
		ft_puthex_s_fd(va_arg(ap, unsigned int), 1, \
				&var->ret, &var->p_ret);
	else if (form == 'X')
		ft_puthex_l_fd(va_arg(ap, unsigned int), 1, \
				&var->ret, &var->p_ret);
	else if (form == 'p')
		ft_putmem_fd(va_arg(ap, unsigned long long), 1, \
				&var->ret, &var->p_ret);
	else if (form == '%')
		ft_putchar_fd(form, 1, &var->ret, &var->p_ret);
}
