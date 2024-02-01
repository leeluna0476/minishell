/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:19:27 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:46:54 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	mark;
	unsigned char	*string;
	size_t			i;

	if (!s || !n)
		return (NULL);
	string = (unsigned char *)s;
	mark = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (string[i] == mark)
			return ((void *)(&string[i]));
		i++;
	}
	return (NULL);
}
