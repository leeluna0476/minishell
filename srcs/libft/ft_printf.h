/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:23:46 by seojilee          #+#    #+#             */
/*   Updated: 2023/11/08 18:03:25 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_variable {
	int		i;
	ssize_t	ret;
	int		p_ret;
}	t_variable;

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd, ssize_t *ret, int *p_ret);
void	ft_putstr_fd(char *s, int fd, ssize_t *ret, int *p_ret);
void	ft_putunbr_fd(unsigned int n, int fd, ssize_t *ret, int *p_ret);
void	ft_putint_fd(int n, int fd, ssize_t *ret, int *p_ret);
void	ft_puthex_s_fd(unsigned int num,
			int fd, ssize_t *ret, int *p_ret);
void	ft_puthex_l_fd(unsigned int num,
			int fd, ssize_t *ret, int *p_ret);
void	ft_putmem_fd(unsigned long long num,
			int fd, ssize_t *ret, int *p_ret);
void	ft_puts(char form, va_list ap, t_variable *var);
int		ft_printf(const char *format, ...);

#endif
