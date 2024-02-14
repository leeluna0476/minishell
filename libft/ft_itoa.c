/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:33:23 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:12:30 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_len(int nb, int *len, int *sign)
{
	if (nb == -2147483648)
	{
		get_len(nb / 10, len, sign);
		(*len)++;
	}
	else if (nb < 0)
	{
		*sign = -1;
		(*len)++;
		get_len(-nb, len, sign);
	}
	else
	{
		if (nb > 9)
			get_len(nb / 10, len, sign);
		(*len)++;
	}
}

static void	insert_num(int nb, char *num_string, int *i)
{
	if (nb == -2147483648)
	{
		insert_num(nb / 10, num_string, i);
		num_string[*i] = 8 + '0';
	}
	else if (nb < 0)
	{
		num_string[0] = '-';
		*i = 1;
		insert_num(-nb, num_string, i);
	}
	else
	{
		if (nb > 9)
			insert_num(nb / 10, num_string, i);
		num_string[*i] = '0' + (nb % 10);
		(*i)++;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	int		i;
	char	*num_string;

	len = 0;
	get_len(n, &len, &sign);
	num_string = ft_calloc(len + 1, sizeof(char));
	if (!num_string)
		return (NULL);
	i = 0;
	insert_num(n, num_string, &i);
	return (num_string);
}
