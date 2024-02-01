/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:21:15 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:52:14 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	s_len_plus_one;
	char	*ret_c;

	if (!s)
		return (NULL);
	ret_c = (char *)s;
	i = 0;
	s_len_plus_one = ft_strlen(s) + 1;
	while (i < s_len_plus_one)
	{
		if (ret_c[i] == (char)c)
			return (&ret_c[i]);
		i++;
	}
	return (0);
}
