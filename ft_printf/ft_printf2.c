/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:32:00 by yusekim           #+#    #+#             */
/*   Updated: 2023/04/06 11:52:32 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	find_len(long n, int base)
{
	size_t	out;

	out = 0;
	if (n <= 0)
		out++;
	while (n)
	{
		out++;
		n /= base;
	}
	return (out);
}

void	fill_nbr(char *str, long n, char format, size_t len)
{
	char	*hexa_base;

	hexa_base = "0123456789abcdef";
	if (format == 'X')
		hexa_base = "0123456789ABCDEF";
	str[len] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n && len--)
	{
		if (format == 'd' || format == 'i' || format == 'u')
		{
			str[len] = n % 10 + '0';
			n /= 10;
		}
		else
		{
			str[len] = hexa_base[n % 16];
			n /= 16;
		}
	}
}

int	ft_putnbr(long n, char format, int base)
{
	size_t	len;
	char	*str;

	if (n == 0)
	{
		len = ft_putchar('0');
		return (len);
	}
	len = find_len(n, base);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (-1);
	fill_nbr(str, n, format, len);
	len = ft_putstr(str);
	free(str);
	return (len);
}

size_t	find_mem_len(unsigned long long nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		len++;
	while (nb)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

int	ft_putmem(unsigned long long nb)
{
	char	*hexa_base;
	size_t	len;
	char	*str;

	if (nb == 0)
	{
		len = ft_putstr("0x0");
		return (len);
	}
	hexa_base = "0123456789abcdef";
	len = find_mem_len(nb);
	str = malloc(sizeof(char) * (len + 3));
	if (!str)
		return (-1);
	str[len + 2] = 0;
	str[0] = '0';
	str[1] = 'x';
	while (nb && len--)
	{
		str[len + 2] = hexa_base[nb % 16];
		nb /= 16;
	}
	len = ft_putstr(str);
	free(str);
	return (len);
}
