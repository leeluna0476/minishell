/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:56:09 by yusekim           #+#    #+#             */
/*   Updated: 2023/04/06 11:54:06 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		detact_f(char *format, va_list ap);
int		ft_putstr(char *s);
int		ft_putchar(int c);
int		ft_putnbr(long n, char format, int base);
int		ft_putmem(unsigned long long nb);

#endif