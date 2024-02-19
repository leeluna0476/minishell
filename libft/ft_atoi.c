/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:21:52 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/01 20:22:04 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long		ret_num;
	const unsigned long	cutoff = ~((long) 1 << ((sizeof(long) * 8) - 1)) / 10;
	const int			cutlim = ~((long) 1 << ((sizeof(long) * 8) - 1)) % 10;

	if (!str)
		return (0);
	i = 0;
	while (is_space(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	ret_num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ret_num > cutoff || (ret_num == cutoff && (str[i] - '0') > cutlim))
			return (-1 * (sign == 1));
		ret_num = (ret_num * 10) + (str[i++] - '0');
	}
	return ((int)ret_num * sign);
}
