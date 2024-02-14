/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:23:03 by seojilee          #+#    #+#             */
/*   Updated: 2024/02/10 19:26:46 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			s_len;
	char			*substring;
	unsigned int	i;
	unsigned int	j;

	if (!s || !len)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_calloc(1, 1));
	if (start + len > s_len)
		len = s_len - start;
	else if (len > s_len)
		len = s_len;
	substring = ft_calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] && i < start + len)
		substring[j++] = s[i++];
	return (substring);
}
