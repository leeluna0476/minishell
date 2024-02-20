/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:36:53 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:55:49 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	need_len;
	char	*hay;
	char	*need;

	if (!haystack || !needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	hay = (char *)haystack;
	need = (char *)needle;
	need_len = ft_strlen(needle);
	i = 0;
	while (hay[i] && len > 0 && i + need_len <= len)
	{
		if (ft_strncmp(&hay[i], need, need_len) == 0)
			return (&hay[i]);
		i++;
	}
	return (NULL);
}
