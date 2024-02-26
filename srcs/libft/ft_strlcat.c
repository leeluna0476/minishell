/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:21:59 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:53:57 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!src)
		return (0);
	if (!dst && !dstsize)
		return (ft_strlen(src) + dstsize);
	len = 0;
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	j = 0;
	while (src[j] && i + 1 < dstsize)
		dst[i++] = src[j++];
	if (i < dstsize)
		dst[i] = '\0';
	while (src[j])
	{
		i++;
		j++;
	}
	len = i;
	return (len);
}
