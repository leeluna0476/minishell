/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:19:53 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 12:49:11 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	greater_address(void *dst, const void *src)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (dst_ptr >= src_ptr)
		return (1);
	else
		return (-1);
}

static void	greater(unsigned char *dst, unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	smaller(unsigned char *dst, unsigned char *src, size_t len)
{
	int	i;

	i = (int)len - 1;
	while (i >= 0)
	{
		dst[i] = src[i];
		i--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (!dst || !src)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (greater_address(dst, src) == -1)
		greater(dst_ptr, src_ptr, len);
	else
		smaller(dst_ptr, src_ptr, len);
	return (dst);
}
