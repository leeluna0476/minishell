/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:21:24 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:53:03 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	length;

	if (!s || !f)
		return ;
	i = 0;
	length = (unsigned int)ft_strlen(s);
	while (i < length)
	{
		(*f)(i, &s[i]);
		i++;
	}
}
