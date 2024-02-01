/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:22:56 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 14:02:02 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		len;
	int		i[3];

	if (!s1 || !set)
		return (NULL);
	len = 0;
	i[INDEX] = 0;
	while (is_set(set, s1[i[INDEX]++]))
		len++;
	i[JNDEX] = ft_strlen(s1) - 1;
	if (len == i[JNDEX] + 1)
		return (ft_calloc(1, 1));
	while (is_set(set, s1[i[JNDEX]--]))
		len++;
	trimmed_str = ft_calloc(ft_strlen(s1) - len + 1, sizeof(char));
	if (!trimmed_str)
		return (NULL);
	i[INDEX]--;
	i[JNDEX]++;
	i[KNDEX] = 0;
	while (i[INDEX] <= i[JNDEX])
		trimmed_str[i[KNDEX]++] = s1[i[INDEX]++];
	return (trimmed_str);
}
