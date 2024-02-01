/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:18:55 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/20 17:52:39 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	alloc_size;
	char	*ptr;

	alloc_size = count * size;
	if (size && count > ~(size_t)0 / size)
		return (NULL);
	ptr = malloc(alloc_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, alloc_size);
	return ((void *)ptr);
}
