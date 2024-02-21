/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:41:07 by yusekim           #+#    #+#             */
/*   Updated: 2023/04/06 11:53:00 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	int		out;

	out = write(1, &c, 1);
	return (out);
}

int	ft_putstr(char *s)
{
	int		out;
	int		len;

	out = 0;
	len = 0;
	if (s == NULL)
		s = "(null)";
	while (s[len])
	{
		out = ft_putchar(s[len]);
		if (out == -1)
			return (out);
		len++;
	}
	return (len);
}

int	detact_f(char *format, va_list ap)
{
	int	temp;

	temp = 0;
	if (*format == 'c')
		temp = ft_putchar(va_arg(ap, unsigned int));
	if (*format == 's')
		temp = ft_putstr(va_arg(ap, char *));
	if (*format == 'i' || *format == 'd')
		temp = ft_putnbr(va_arg(ap, int), *format, 10);
	if (*format == 'u')
		temp = ft_putnbr(va_arg(ap, unsigned int), *format, 10);
	if (*format == 'x' || *format == 'X')
		temp = ft_putnbr(va_arg(ap, unsigned int), *format, 16);
	if (*format == 'p')
		temp = ft_putmem((unsigned long long)va_arg(ap, void *));
	if (*format == '%')
		temp = ft_putchar('%');
	return (temp);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;
	int		tmp;

	res = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			tmp = detact_f((char *)(++format), ap);
			if (tmp == -1)
				return (-1);
			res += tmp;
			format++;
			continue ;
		}
		tmp = write(1, format, 1);
		if (tmp == -1)
			return (tmp);
		res++;
		format++;
	}
	va_end(ap);
	return (res);
}
